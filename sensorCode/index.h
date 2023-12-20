const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" rel="stylesheet">
    <!-- <link rel="stylesheet" href="style.css"> -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/9h057-404/project-military-robot@main/style3.css">
    <title>Robot control room</title>
</head>
<body>
    <section>
        <img src="https://cdn.jsdelivr.net/gh/9h057-404/project-military-robot@main/background.png" alt="" class="bg">
        <img src="https://cdn.jsdelivr.net/gh/9h057-404/project-military-robot@main/army.png" alt="" class="tank">
        <img src="https://cdn.jsdelivr.net/gh/9h057-404/project-military-robot@main/foreground.png" alt="" class="fg">
        <div class="login">
            <h1>Robot Control Room </h1>
            <div class="inputBox">
                <p>
                <i class="icn fa fa-thermometer-half"></i> 
                <span class="dht-labels">&nbsp; Temperature : </span> 
                <span id="TemperatureValue">0</span>
                <sup class="units">&deg;C</sup>
            </p>
            <p>
                <i class="icns fa fa-tint"></i>
                <span class="dht-labels">&nbsp; Humidity : </span>
                <span id="HumidityValue">0</span>
                <sup class="units">%</sup>
            </p>
            <p>
                <i class="icn fa fa-smog"></i> 
                <span class="dht-labels">&nbsp; Air Quality : </span> 
                <span id="AirQualityValue">0</span>
                <sup class="units">&nbsp;ppm</sup>
            </p>

            <!-- pir code start -->
            <p>
                <i class="icn fa fa-running"></i> 
                <span class="dht-labels">&nbsp; Motion Detected: </span> 
                <span id="MotionValue">No</span>
            </p>
            <p id="Alert" style="color: red; display: none;">ALERT! Motion Detected!</p>
            <audio id="alert-sound" src="https://cdn.jsdelivr.net/gh/9h057-404/project-military-robot@main/audio.mp3"></audio>
            <!-- pir code end  -->
            <br>


        <!-- servo motor  -->
            <div class="slidecontainer">
                <input type="range" min="0" max="180" value="3" class="slider" id="myRange1">
                <p>
                    <div class="flex">
                    <i class="aim fa fa-bullseye"></i>&nbsp; <span style="padding-left: 10px; padding-right: 10px;  font-size: 1.5rem; ">Shoot</span>
                    <label class="switch">
                        <!-- <input type="checkbox" onclick="send(this.checked)"> -->
                        <input type="checkbox" id="led-toggle">
                        <span class="slider1 round"></span>
                    </label>
                    <div style="display: none;">
                        LED State: <span id="state">NA</span>
                    </div>
                
                <span style="padding-left: 150px; font-size: 1.5rem;"><i class="aim fas fa-crosshairs"></i> &nbsp; Aim Angle : <span id="demo1"></span></span>
                </p></div>
            </div>

            <div class="slidecontainer">
                <input type="range" min="0" max="180" value="90" class="slider" id="myRange2">
                <p><i class="aim fas fa-crosshairs"></i> &nbsp; Pan Servo: <span id="demo2"></span></p>
            </div>
            <p>
                <i class="clock far fa-clock"></i>
                <span class="clock-info">Time :</span>
                <span id="time" style="font-size:1.4rem;"></span>
                <br>            
                <i class="clock far fa-calendar-alt"></i>
                <span class="clock-info">Date :</span>
                <span id="date" style="font-size:1.4rem;"></span>
            </P>
            </div>
        </div>
    </section>
    <script src="https://cdn.jsdelivr.net/gh/9h057-404/project-military-robot@main/app4.js"></script>
</body>
</html>
)=====";