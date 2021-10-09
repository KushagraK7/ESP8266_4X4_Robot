
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }

      .container {
        height: 200px;
        position: relative;
      }

      .center {
        margin: 0;
        position: absolute;
        top: 50%;
        left: 50%;
        -ms-transform: translate(-50%, -50%);
        transform: translate(-50%, -50%);
      }
      
      .slidecontainer {
        width: 100%;
      }

      .slider {
        -webkit-appearance: none;
        width: 50%;
        height: 15px;
        border-radius: 5px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }

      .slider:hover {
        opacity: 1;
      }

      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #FFA500;
        cursor: pointer;
      }

      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #FFA500;
        cursor: pointer;
      }
    
    .box-group box{
      background-color: #808080;
      width: 300px;
      border: 15px grey;
      color: grey;
      padding: 50px;
      margin: 20px;
    }
	  
	  .btn-group button {
	  
		
		background-color: #FFA500; /* Orange background */
		border: none; 
		color: white; /* White text */
		padding: 15px 45px; /* Some padding */
		cursor: pointer; /* Pointer/hand icon */
		
	  }

/* Clear floats (clearfix hack) */
.btn-group:after {
  content: "";
  clear: both;
  display: table;
}

.btn-group button:not(:last-child) {
  border-right: none; /* Prevent double borders */
}

/* Add a background color on hover */
.btn-group button:hover {
  background-color: #FF8C00;
}
    </style>
  </head>
  <body style="background-color:grey;">
  
	

    <h1>Wheeled Robot Control Panel</h1>
  

      <p>Max Speed : <span id="v1"></span></p>
	    <p>Direction : <span id="dir"></span></p>

    <div class="slidecontainer">
      <input 
	  type="range" orient="vertical" min="0" max="100" value="0" class="slider" id="myRange"
	  >
	  
	</div>
	
  

    <div class="container">
        <div class="center"> 
            <div class="btn-group">
          	  <button Forward onmousedown="forward()" ontouchstart="forward()" onmouseup="stop()" ontouchend="stop()" > Forward </button>
            </div>

            <div class="box-group">
            <button> </button>
            </div>

            <div class="btn-group">
              <button Left onmousedown="Left()" ontouchstart="Left()" onmouseup="stop()" ontouchend="stop()"> Left </button>
              <button Stop onclick= "stop()" > Stop </button>
              <button Right onmousedown="Right()" ontouchstart="Right()" onmouseup="stop()" ontouchend="stop()"> Right </button>
            </div>

            <div class="box-group">
            <button> </button>
            </div>

            <div class="btn-group">
          	  <button Reverse onmousedown="reverse()" ontouchstart="reverse()" onmouseup="stop()" ontouchend="stop()"> Reverse </button>
            </div>
        </div>   
    </div>
		

    <script>
      function sendData(pos) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setPOS?POS="+pos, true);
        xhttp.send();
      }

      function sendLDir(Ldir) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setLDir?LDir="+Ldir, true);
        xhttp.send();
      }

      function sendRDir(Rdir) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        xhttp.open("GET", "setRDir?RDir="+Rdir, true);
        xhttp.send();
      }

		
		function reverse() {
			dir.innerHTML = "Reverse";
      
      sendLDir("-1");
      sendRDir("-1");		
    }
		
		function forward() {
			dir.innerHTML = "Forward";
      
      sendLDir("1");
      sendRDir("1");
		}

		function stop()	{
      sendLDir("0");
      sendRDir("0");
		}

    function Left(){
      dir.innerHTML = "Left";
      sendLDir("1");
      sendRDir("-1");
    }

    function Right(){
      dir.innerHTML = "Right";
      sendLDir("-1");
      sendRDir("1");
    }
  

      var slider = document.getElementById("myRange");
      var output = document.getElementById("v1");
      output.innerHTML = slider.value;
	  
	  
      slider.oninput = function() {
        output.innerHTML = this.value;
        sendData(output.innerHTML);
      }
    </script>

  </body>
</html>

)=====";
