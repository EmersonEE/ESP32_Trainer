function getPickerWidth() {
    const root = document.querySelector(':root');
    const rootStyle = getComputedStyle(root);
    return Number(rootStyle.getPropertyValue('--picker-width').replace("px", ""));
}

const pickerWidth = getPickerWidth();

const colorPicker = new iro.ColorPicker('#color', {
    width: pickerWidth,
    color: "rgb(255, 0, 0)",
    borderWidth: 2,
    borderColor: "#fff",
    wheelLightness: false,
    sliderSize: pickerWidth / 11,
});
colorPicker.color.value = 0; // Initially the LED is off

function changeBackgroundColor(rgb) {
    document.body.style.backgroundColor = "rgb(" + rgb.r + ", " + rgb.g + ", " + rgb.b + ")";
}

function sendColorToWS(rgb) {
    let result = {
      action: 'change',
      data: {
        r: rgb.r,
        g: rgb.g,
        b: rgb.b,
      }
    };
  
    socket.send(JSON.stringify(result));
    console.log("Data sent to server: " + JSON.stringify(result));
  }

let debounce = null;
colorPicker.on('input:change', function(value) {
    if (!debounce) {
        changeBackgroundColor(value.rgb);
        sendColorToWS(value.rgb);
    }
    debounce = setTimeout(() => {
        debounce = undefined;
    }, 100);
});