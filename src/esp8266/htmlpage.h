	const char main_page[] = R"=====(
<html>
<head>
 <meta http-equiv="refresh" content="10" >
 <style>
table, th, td {
    border: 1px solid black;
    font-size: 30px;
}
</style>
 <title>Sensors</title>
</head>

<body>
<table>
<tr>
<th>Sensor</th>
<th>Value</th>
</tr>


<tr>
<td>Temperature</td>
<td>@@@t@@@</td>
</tr>

<tr>
<td>Humidity</td>
<td>@@@h@@@</td>
</tr>


<tr>
<td>Temperature</td>
<td>@@@t1@@@</td>
</tr>

<tr>
<td>Pressure</td>
<td>@@@p1@@@</td>
</tr>

<tr>
<td>Current Sensor value</td>
<td>@@@s@@@</td>
</tr>

<tr>
<td>Current</td>
<td>@@@c@@@</td>
</tr>


</table>

<br>

@@@n@@@

</body>

</html>
)=====";