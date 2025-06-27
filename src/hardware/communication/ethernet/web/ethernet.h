#ifndef _WEB_PAGE_H_
#define _WEB_PAGE_H_

#define web_configuration_page  "<!DOCTYPE html>"\
"<html lang=\"pl\">"\
"<head>"\
  "<meta charset=\"UTF-8\" />"\
  "<title>Ustawienia sieciowe</title>"\
  "<style>"\
    "body {"\
      "background-color: #2a0057;"\
      "font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;"\
      "color: #eee;"\
      "display: flex;"\
      "justify-content: center;"\
      "align-items: center;"\
      "height: 100vh;"\
      "margin: 0;"\
    "}"\
    ".container {"\
      "background-color: #3f0070;"\
      "padding: 3rem 2.5rem;"\
      "border-radius: 6px;"\
      "width: 420px;"\
      "box-sizing: border-box;"\
    "}"\
    "h1 {"\
      "font-weight: 700;"\
      "font-size: 2.8rem;"\
      "text-align: center;"\
      "margin-bottom: 2rem;"\
      "letter-spacing: 0.15em;"\
      "color: #c4a7ff;"\
    "}"\
    "label {"\
      "display: block;"\
      "margin-top: 1.2rem;"\
      "font-weight: 600;"\
      "font-size: 1rem;"\
    "}"\
    "input[type=\"text\"] {"\
      "width: 100%;"\
      "padding: 0.5rem 0.75rem;"\
      "margin-top: 0.4rem;"\
      "border: 1px solid #5e3ebd;"\
      "border-radius: 4px;"\
      "font-size: 1rem;"\
      "background-color: #3f0070;"\
      "color: #eee;"\
      "outline: none;"\
      "box-sizing: border-box;"\
    "}"\
    "input[type=\"text\"]:focus {"\
      "border-color: #7a52ff;"\
      "background-color: #3f0070;"\
    "}"\
    "input[type=\"submit\"] {"\
      "margin-top: 2rem;"\
      "width: 100%;"\
      "padding: 0.75rem;"\
      "background-color: #7a52ff;"\
      "border: none;"\
      "border-radius: 4px;"\
      "font-size: 1.25rem;"\
      "color: white;"\
      "cursor: pointer;"\
      "font-weight: 700;"\
      "transition: background-color 0.3s ease;"\
    "}"\
    "input[type=\"submit\"]:hover {"\
      "background-color: #956cff;"\
    "}"\
    "#responseMsg {"\
      "margin-top: 1.2rem;"\
      "font-size: 1rem;"\
      "text-align: center;"\
      "min-height: 1.3em;"\
      "color: #b9d9ff;"\
    "}"\
  "</style>"\
"</head>"\
"<body>"\
  "<div class=\"container\">"\
    "<h1>GRYFSMART</h1>"\
    "<form id=\"networkForm\">"\
      "<label for=\"ip\">Adres IP</label>"\
      "<input type=\"text\" id=\"ip\" name=\"ip\" placeholder=\"np. 192.168.40.85\" required />"\
      "<label for=\"mask\">Maska podsieci</label>"\
      "<input type=\"text\" id=\"mask\" name=\"mask\" placeholder=\"np. 255.255.255.0\" required />"\
      "<label for=\"gateway\">Brama</label>"\
      "<input type=\"text\" id=\"gateway\" name=\"gateway\" placeholder=\"np. 192.168.40.1\" required />"\
      "<input type=\"submit\" value=\"Zapisz\" />"\
    "</form>"\
    "<div id=\"responseMsg\"></div>"\
  "</div>"\
  "<script>"\
    "const ipField = document.getElementById(\"ip\");"\
    "const maskField = document.getElementById(\"mask\");"\
    "const gatewayField = document.getElementById(\"gateway\");"\
    "const form = document.getElementById(\"networkForm\");"\
    "const responseMsg = document.getElementById(\"responseMsg\");"\
    "ipField.addEventListener(\"input\", () => {"\
      "const ip = ipField.value.trim();"\
      "const regex = /^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.\\d{1,3}$/;"\
      "const match = ip.match(regex);"\
      "if (ip === \"\") {"\
        "maskField.value = \"\";"\
        "gatewayField.value = \"\";"\
        "return;"\
      "}"\
      "if (match) {"\
        "const gatewayGuess = `${match[1]}.${match[2]}.${match[3]}.1`;"\
        "if (!maskField.value) {"\
          "maskField.value = \"255.255.255.0\";"\
        "}"\
        "if (!gatewayField.value) {"\
          "gatewayField.value = gatewayGuess;"\
        "}"\
      "}"\
    "});"\
    "form.addEventListener(\"submit\", async (e) => {"\
      "e.preventDefault();"\
      "const data = {"\
        "ip: ipField.value.trim(),"\
        "mask: maskField.value.trim(),"\
        "gateway: gatewayField.value.trim(),"\
      "};"\
      "responseMsg.textContent = \"Wysyłanie...\";"\
      "try {"\
        "const response = await fetch(\"/set-ip\", {"\
          "method: \"POST\","\
          "headers: { \"Content-Type\": \"application/json\" },"\
          "body: JSON.stringify(data),"\
        "});"\
        "if (!response.ok) throw new Error(`Błąd serwera: ${response.statusText}`);"\
        "const text = await response.text();"\
        "responseMsg.textContent = \"Odpowiedź serwera: \" + text;"\
      "} catch (err) {"\
        "responseMsg.textContent = \"Błąd: \" + err.message;"\
      "}"\
    "});"\
  "</script>"\
"</body>"\
"</html>"

#endif /* _WEB_PAGE_H_ */


