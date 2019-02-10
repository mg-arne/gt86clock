function updateConfig(params) {
  var http = new XMLHttpRequest();
  var url = "/config";
  http.open("GET", [url,params].join('?'), true);
  http.send();
  console.log([url,params].join('?'));
}

function changeMode() {
  var http = new XMLHttpRequest();
  var url = "/config";
  var params = "mode=";
  params += document.getElementById("modeCurrent").value; 
  http.open("GET", [url,params].join('?'), true);
  http.send();
  console.log([url,params].join('?'));
}

function displayLineChart() {
  var dataDate = JSON.parse(dataDateJson);
  document.getElementById('datetime').innerHTML = dataDate[0].date;

  var dataConfig = JSON.parse(dataConfigJson);
  document.getElementById("modeCurrent").value = dataConfig[0].modeCurrent;
  document.getElementsByName("pressureBar")[1-dataConfig[0].pressureBar].checked = true;
  document.getElementsByName("temperatureCelsius")[1-dataConfig[0].temperatureCelsius].checked = true;
  document.getElementsByName("clock24h")[1-dataConfig[0].clock24h].checked = true;
  document.getElementsByName("o2afr")[1-dataConfig[0].o2afr].checked = true;


  Chart.defaults.global.responsive = true;
  Chart.defaults.global.elements.line.fill = false;
  new Chart(document.getElementById("line-chart"), {
    type: 'line',
    data: {
      labels: [
        '2019-01-01 12:00',
        '2019-01-01 12:01',
        '2019-01-01 12:02',
        '2019-01-01 12:03',
        '2019-01-01 12:04',
        '2019-01-01 12:05',
        '2019-01-01 12:06',
        '2019-01-01 12:06',
        '2019-01-01 12:07',
        '2019-01-01 12:08'
        ],
      datasets: [
        {
          label: "Coolant",
          borderColor: "#3e95cd",
          data: [
            -10, 25, 50, 66, 77, 83, 88, 93, 97, 98
          ]
        },
        {
          label: "Oil",
          borderColor: "#8e5ea2",
          data: [
            -10, 20, 45, 60, 73, 83, 91, 98, 103, 108
          ]
        }
      ]
    },
    options : {
      title: {
        display: true,
        text: 'Temperature'
      },
     scales: {
       yAxes: [
         {
           scaleLabel: {
             display: true,
             labelString: '°C'
            }
          }
        ]
      }
    }
  });
 }
