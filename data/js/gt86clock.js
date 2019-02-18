var chart;

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
  http.open("GET", url+params, true);
  http.send();
  console.log(url+params);
}

function addZero(i) {
  if (i < 10) {
    i = "0" + i;
  }
  return i;
}

function removeData() {
    chart.data.labels.pop();
    chart.data.datasets.forEach((dataset) => {
        dataset.data.pop();
    });
}

function changeJson() {
  var http = new XMLHttpRequest();
  var url = document.getElementById("json").value;
  var dateFile = new Date(url.substring(16,20), url.substring(20,22), url.substring(22,24), url.substring(24,26), url.substring(26,28));
  var dateLabel = new Date();

  http.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var dataGraph = JSON.parse("{\"data\": ["+http.responseText+"]}");
      var i=0;
      removeData();
      for (var line in dataGraph['data']) {
        for (var value in dataGraph['data'][line]) {
          if ( i > 0 ) {
            dateLabel.setTime(dateFile.getTime()+parseInt(value));
            chart.data.labels[i-1] = dateLabel.getFullYear()+":"+addZero(dateLabel.getMonth())+":"+addZero(dateLabel.getDate())+" "+addZero(dateLabel.getHours())+":"+addZero(dateLabel.getMinutes())+":"+addZero(dateLabel.getSeconds());
            chart.data.datasets[0].data[i-1] = dataGraph['data'][line][value][1];
            chart.data.datasets[1].data[i-1] = dataGraph['data'][line][value][0];
          }
        };
        i++;
      }
      chart.update();
    }
  };
  http.open("GET", url, true);
  http.send();
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

  var dataJsonContent = JSON.parse(dataJson);
  var selectJson = document.getElementById("json");

  for (var file in dataJsonContent) {
    var el = document.createElement("option");
    el.text = dataJsonContent[file].file+" ("+dataJsonContent[file].size+" bytes)";
    el.value = dataJsonContent[file].file;
    selectJson.appendChild(el);
  }

  Chart.defaults.global.responsive = true;
  Chart.defaults.global.elements.line.fill = false;
  chart = new Chart(document.getElementById("line-chart"), {
    type: 'line',
    data: {
      datasets: [
        {
          label: "Coolant",
          borderColor: "#3e95cd"
        },
        {
          label: "Oil",
          borderColor: "#8e5ea2"
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

  changeJson();
 }
