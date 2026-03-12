#include <SPI.h>
#include <Ethernet2.h>
class Ethernet {
public:
  Eternet()
    : {};
  void init() {
    EthernetServer server(80);
  }
  void connect() {
    EthernetServer server(localPort);
    Ethernet.begin(mac, ip);
    server.begin();
    EthernetClient client = server.available();
    if (client) {
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          if (startGet == true)  // данные после '?'
            getData += c;
          if (c == '?')  // начало сбора данных после '?'
            startGet = true;
          if (c == '\n' && currentLineIsBlank)  // окончание получения
          {
            if (getData.length() < 1)  // запрос без get-данных
            {
              pinState[0] = 0;
              pinState[1] = 0;
            } else {
              pinState[0] = int(getData[5]) - 48;
              pinState[1] = int(getData[12]) - 48;
            }
            // отправка заголовков клиенту
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // формирование страницы ответа
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<h3>Ethernet shield + LEDS</h3>");
            client.println("<form method='get'>");
            // светодиод 1
            client.print("<div>");
            client.print("led1 off<input type='radio' name='led1' value=0 onclick='document.getElementById(\"submit\").click();' ");
            if (pinState[0] == 0)
              client.print("checked");
            client.println(">");
            client.print("<input type='radio' name='led1' value=1 onclick='document.getElementById(\"submit\").click();' ");
            if (pinState[0] == 1)
              client.print("checked");
            client.println("> on");
            client.println("</div>");
            // светодиод 2
            client.print("<div>");
            client.print("led2 off<input type='radio' name='led2' value=0 onclick='document.getElementById(\"submit\").click();' ");
            if (pinState[1] == 0)
              client.print("checked");
            client.println(">");
            client.print("<input type='radio' name='led2' value=1 onclick='document.getElementById(\"submit\").click();' ");
            if (pinState[1] == 1)
              client.print("checked");
            client.println("> on");
            client.println("</div>");
            client.println("<input type='submit' id='submit' style='visibility:hidden;' value='Refresh'>");
            client.println("</form>");
            client.println("</html>");
            break;
          }
          if (c == '\n') {
            currentLineIsBlank = true;
          } else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }
      }
    }
    // задержка для получения клиентом данных
    delay(1);
    // закрыть соединение
    client.stop();
  }
private:
  const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  const IPAddress localhost(127, 0, 0, 1);
  const int localPort = 80;
  bool startGet = false;
  IPAddress app;
}