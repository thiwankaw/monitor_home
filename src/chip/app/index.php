<!doctype html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Solar Monitor</title>
    <meta http-equiv="refresh" content="60" >
    <script src="js/Chart.bundle.js"></script>

</head>
<body>
<div class="box">
    <canvas id="lineChart" height="450" width="800"></canvas>
</div>




<?php
$servername = "localhost";
$username = "data_user";
$password = "data_pass";
$database = "sensor_data";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// $sql = "SELECT createdTime, svalue from current where createdTime > '2017/12/13 07:00:00' order by createdTime ";
   $sql = "SELECT createdTime, svalue from current where createdTime > DATE_ADD(CURRENT_DATE(), INTERVAL 6 HOUR) order by createdTime";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    $a="[";
    $b="[";
    while($row = $result->fetch_assoc()) {
        $a=$a. "'" .$row["createdTime"]  . "',";
        // 110 is taken from the battery capacity
        $b=$b. ($row["svalue"]*110)  . ",";
    }
    $a=substr($a,0,-1);
    $b=substr($b,0,-1);
    $a=$a . "]";
    $b=$b . "]";
    // echo $a;
} else {
    echo "0 results";
}
$conn->close();


?>


<script>new Chart(document.getElementById("lineChart"), {
        "type": "bar",
        "data": {
            "labels": <?=$a?>,
            "datasets": [{
                "label": "Solar power generation",
                "data": <?=$b?>,
                "fill": false,
                "backgroundColor" : "rgb(200, 100, 50)",
                "borderColor": "rgb(75, 192, 192)",
                "lineTension": 0.1
            }]
        },
        "options": {}
    });</script>



</body>
</html>