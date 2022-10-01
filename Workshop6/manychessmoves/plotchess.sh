#!/bin/bash

# run with:
#	./manychessmoves 40 board moves | ./plotchess.sh > plot.html
# then open  plot.html  in your browser

# input lines:
#	1630565254, 7/8 running, 8/20 complete

COLOUR="magenta"
TITLE="processes running over time"

function top_half() {
cat << THE_END
<html>
<head>
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <script type="text/javascript">
    google.charts.load('current', {'packages':['corechart']});
    google.charts.setOnLoadCallback(drawChart);

    function drawChart() {
      var data = google.visualization.arrayToDataTable([
	['time', 'nrunning'],
THE_END
}

function process_stdin() {
	  grep '^[0-9]' \
	| cut '-d ' -f1,2,4 \
	| sed 's,/, ,g' \
	|	while read time running ncores completed max ; do
		    echo "          [ $time, $running ],"
		done
}

function bottom_half() {
cat << THE_END
        ]);
	var options = {
	  title: '$TITLE',
	  titleTextStyle: {fontSize: 12, bold: false},
	  fontSize: 10, pointSize: 2,
	  areaOpacity: 0.6,
	  legend: { position: 'in', maxLines: 1 },
	  colors: ['$COLOUR'],
	  chartArea: {backgroundColor: '#eee', left: 40, top: 20, bottom: 30},
	  vAxis: { title: 'N-running', format: 'decimal', minValue: 0 },
	  hAxis: { title: 'running-time (msecs)', format: 'decimal', gridlines: {count: 7} },
	};
	var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

	chart.draw(data, options);
    }
  </script>
</head>

<body>
  <div id="curve_chart" style="width: 800px; height: 400px"></div>
</body>
</html>
THE_END
}

# --------------------------------------------------------------------

top_half
    process_stdin
bottom_half

