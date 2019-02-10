function updateConfig(params) {
  var http = new XMLHttpRequest();
  var url = "/config";
  http.open("GET", [url,params].join('?'), true);
  http.send();
  console.log([url,params].join('?'));
}

function displayLineChart() {
  var dataDate = JSON.parse(dataDateJson);
  document.getElementById('datetime').innerHTML = dataDate[0].date;

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
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29
          ]
        },
        {
          label: "Oil",
          borderColor: "#8e5ea2",
          data: [
            0, 1, 1, 2, 3, 5, 8, 13, 21, 34
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
