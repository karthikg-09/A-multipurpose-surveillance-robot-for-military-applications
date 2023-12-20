setInterval(function() {
    // Call a function repetatively with 2 Second interval
    getTemperatureData();
    getHumidityData();
    getAirQualityData();
    getMotionData();
  }, 2000); 
  
  setInterval(function() {
    // Call a function repetatively with 1 Second interval
    Time_Date();
  }, 1000); 

  function getTemperatureData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("TemperatureValue").innerHTML =
        this.responseText;
      }
    };
    xhttp.open("GET", "readTemperature", true);
    xhttp.send();
  }

  function getHumidityData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
      document.getElementById("HumidityValue").innerHTML =
      this.responseText;
      }
    };
    xhttp.open("GET", "readHumidity", true);
    xhttp.send();
  }

  function getAirQualityData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("AirQualityValue").innerHTML =
        this.responseText;
      }
    };
    xhttp.open("GET", "readGas", true);
    xhttp.send();
  }

  // pir starts here 
  function getMotionData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var motionValue = this.responseText;
            document.getElementById("MotionValue").innerHTML = motionValue;
            if (motionValue == "Yes") {
                document.getElementById("Alert").style.display = "block";
                document.getElementById("alert-sound").play(); // Play the sound
            } else {
                document.getElementById("Alert").style.display = "none";
            }
        }
    };
    xhttp.open("GET", "readPIR", true);
    xhttp.send();
  }

  // pir ends here 


  function sendData(pos1, pos2) {
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
    console.log(this.responseText);
  }
};
xhttp.open("GET", "setPOS?servoPOS1="+pos1+"&servoPOS2="+pos2, true);
xhttp.send();
} 
  var slider1 = document.getElementById("myRange1");
  var output1 = document.getElementById("demo1");
  output1.innerHTML = slider1.value;
  slider1.oninput = function() {
    output1.innerHTML = this.value;
    sendData(output1.innerHTML, output2.innerHTML);
  }  
  var slider2 = document.getElementById("myRange2");
  var output2 = document.getElementById("demo2");
  output2.innerHTML = slider2.value;
  slider2.oninput = function() {
    output2.innerHTML = this.value;
    sendData(output1.innerHTML, output2.innerHTML);
  }        
       



  function Time_Date() {
    var t = new Date();
    document.getElementById("time").innerHTML = t.toLocaleTimeString();
    var d = new Date();
    const dayNames = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday","Saturday"];
    const monthNames = ["January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"];
    document.getElementById("date").innerHTML = dayNames[d.getDay()] + ", " + d.getDate() + "-" + monthNames[d.getMonth()] + "-" + d.getFullYear();
  }

// laser control

document.getElementById("led-toggle").addEventListener("change", function() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
          document.getElementById("state").innerHTML = this.responseText;
      }
  };
  xhttp.open("GET", "led_set?state=" + Number(this.checked), true);
  xhttp.send();
});