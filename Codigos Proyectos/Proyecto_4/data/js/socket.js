let socket = new WebSocket(WEBSOCKET_ADDRESS);

socket.onopen = function(e) {
  console.log("[open] Connection established");
  console.log("Sending to server");
  socket.send("{ 'action': 'init' }");
};

socket.onmessage = function(event) {
  let data = JSON.parse(event.data);

  colorPicker.color.red = data.r;
  colorPicker.color.green = data.g;
  colorPicker.color.blue = data.b;
  changeBackgroundColor(data);

  console.log(`[message] Data received from server: ${event.data}`);
};

socket.onclose = function(event) {
  if (event.wasClean) {
    console.log(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
  } else {
    console.log('[close] Connection died');
  }
};

socket.onerror = function(error) {
  console.log(`[error]`);
};