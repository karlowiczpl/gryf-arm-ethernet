#ifndef _MENU_PAGE_H_
#define _MENU_PAGE_H_

#define index_page "<!DOCTYPE html>"\
"<html lang=\"pl\">"\
"<head>"\
  "<meta charset=\"UTF-8\">"\
  "<title>Menu Główne</title>"\
  "<style>"\
    "body {"\
      "font-family: Arial, sans-serif;"\
      "background-color: #f0f0f0;"\
      "margin: 0;"\
      "padding: 2rem;"\
      "text-align: center;"\
    "}"\
    ".menu-button {"\
      "background-color: #7a52ff;"\
      "color: white;"\
      "border: none;"\
      "padding: 1rem 2rem;"\
      "font-size: 1.2rem;"\
      "border-radius: 6px;"\
      "cursor: pointer;"\
      "transition: background-color 0.3s;"\
    "}"\
    ".menu-button:hover {"\
      "background-color: #956cff;"\
    "}"\
  "</style>"\
"</head>"\
"<body>"\
  "<h1>Menu Główne</h1>"\
  "<button class=\"menu-button\" onclick=\"goToNetworkConfig()\">Network Configuration</button>"\
  "<script>"\
    "function goToNetworkConfig() {"\
      "window.location.href = 'web_configuration.html';"\
    "}"\
  "</script>"\
"</body>"\
"</html>"

#endif /* _MENU_PAGE_H_ */

