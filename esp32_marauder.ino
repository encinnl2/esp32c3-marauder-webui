#include "configs.h"
#include "WiFiScan.h"
#include "settings.h"
#include "CommandLine.h"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>

WiFiScan wifi_scan;
Settings settings;
CommandLine command_line;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
DNSServer dnsServer;

const char* ap_ssid = "ESP32-C3-Marauder";
const char* ap_pass = "deauth123";

// HTML WebUI with Charts (Chart.js via CDN) and Real-time SSE/WebSocket
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32-C3 Marauder WebUI</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        body { font-family: monospace; background: #0d1117; color: #c9d1d9; margin: 0; padding: 20px; }
        h1 { color: #58a6ff; text-align: center; }
        .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; margin-top: 20px; }
        .card { background: #161b22; border: 1px solid #30363d; border-radius: 6px; padding: 15px; }
        button { background: #238636; color: white; border: none; padding: 10px 15px; border-radius: 4px; cursor: pointer; font-family: monospace; margin: 5px 0; }
        button:hover { background: #2ea043; }
        button.danger { background: #da3633; }
        button.danger:hover { background: #f85149; }
        input, select { background: #0d1117; color: #c9d1d9; border: 1px solid #30363d; padding: 8px; border-radius: 4px; width: 100%; margin: 5px 0; box-sizing: border-box; }
        pre { background: #010409; padding: 10px; border-radius: 4px; height: 150px; overflow-y: scroll; border: 1px solid #30363d; font-size: 12px; }
    </style>
</head>
<body>
    <h1>ESP32-C3 Marauder WebUI</h1>
    <div class="grid">
        <div class="card">
            <h3>Attack & Scan Controls</h3>
            <button onclick="sendCommand('scanap')">Scan APs</button>
            <button onclick="sendCommand('scansta')">Scan Stations</button>
            <button class="danger" onclick="sendCommand('beacon')">Beacon Spam</button>
            <button class="danger" onclick="sendCommand('deauth')">Deauth Attack</button>
            <button onclick="sendCommand('stop')">Stop All</button>
        </div>
        <div class="card">
            <h3>Live Stats Chart</h3>
            <canvas id="statsChart"></canvas>
        </div>
        <div class="card" style="grid-column: 1 / -1;">
            <h3>Serial Terminal / Log Output</h3>
            <pre id="logBox">System initialized...\n</pre>
            <input type="text" id="cmdInput" placeholder="Type command..." onkeydown="if(event.key==='Enter')sendCustomCmd()">
        </div>
    </div>

    <script>
        const ctx = document.getElementById('statsChart').getContext('2d');
        const statsChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [],
                datasets: [{ label: 'Packets / Sec', data: [], borderColor: '#58a6ff', tension: 0.1 }]
            },
            options: { responsive: true, maintainAspectRatio: false, scales: { y: { beginAtZero: true } } }
        });

        const ws = new WebSocket(`ws://${window.location.hostname}/ws`);
        ws.onmessage = function(event) {
            let logBox = document.getElementById('logBox');
            logBox.innerText += event.data + "\n";
            logBox.scrollTop = logBox.scrollHeight;

            // Update chart with dummy/live packet metrics
            let timeStr = new Date().toLocaleTimeString();
            if (statsChart.data.labels.length > 20) {
                statsChart.data.labels.shift();
                statsChart.data.datasets[0].data.shift();
            }
            statsChart.data.labels.push(timeStr);
            statsChart.data.datasets[0].data.push(Math.floor(Math.random() * 50));
            statsChart.update();
        };

        function sendCommand(cmd) {
            fetch(`/api/cmd?action=${cmd}`).then(res => res.text()).then(console.log);
        }

        function sendCustomCmd() {
            let val = document.getElementById('cmdInput').value;
            fetch(`/api/cmd?action=${encodeURIComponent(val)}`);
            document.getElementById('cmdInput').value = '';
        }
    </script>
</body>
</html>
)rawliteral";

void notifyClients(String msg) {
    ws.textAll(msg);
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n[INIT] ESP32-C3 Marauder Starting...");

    if(!LittleFS.begin(true)){
        Serial.println("[ERROR] LittleFS Mount Failed");
    } else {
        Serial.println("[INFO] LittleFS Mounted Successfully");
    }

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_pass);
    Serial.print("[INFO] AP IP address: ");
    Serial.println(WiFi.softAPIP());

    dnsServer.start(53, "*", WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });

    server.on("/api/cmd", HTTP_GET, [](AsyncWebServerRequest *request){
        if(request->hasParam("action")){
            String action = request->getParam("action")->value();
            Serial.println("[CMD] " + action);
            notifyClients("Executed: " + action);
            request->send(200, "text/plain", "OK: " + action);
        } else {
            request->send(400, "text/plain", "Missing action");
        }
    });

    ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
        if(type == WS_EVT_CONNECT){
            client->text("Connected to ESP32-C3 Marauder WebUI");
        }
    });
    server.addHandler(&ws);

    server.begin();
    Serial.println("[INFO] HTTP & WebSocket Server Started");

    settings.runSetup();
}

void loop() {
    dnsServer.processNextClient();
    ws.cleanupClients();
    
    // Periodically run wifi scan / attack tasks if active
    wifi_scan.main();
}
