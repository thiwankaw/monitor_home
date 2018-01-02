<?php


// ip address of the esp8266
$html = get_data('http://192.168.8.202/');

/*** a new dom object ***/
$dom = new domDocument;

/*** load the html into the object ***/
$dom->loadHTML($html);


$servername = "localhost";
$username = "data_user";
$password = "data_pass";
$database = "sensor_data";

$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

/* echo "Connected successfully"; */


$rows = $dom->getElementsByTagName('td');

$n = 0;
foreach ($rows as $row) {
    $n = $n + 1;
    if ($n == 12) {
        $v = $row->textContent;
        saveData('current',$v,$conn);
    }
}

$conn->close();


/* gets the data from a URL */
function get_data($url)
{
    $ch = curl_init();
    $timeout = 5;
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
    $data = curl_exec($ch);
    curl_close($ch);
    return $data;
}


function saveData($key,$value,$conn){
    $sql = "insert into samples(application,skey,svalue) values('iot','". $key . "','" . $value . "')";


    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}


?>
