<?php
$username = "ivarqxyg_admin";
$password = "slalom@2";
$host = "localhost";
$database = "ivarqxyg_mapit_db";

// Make the connect to MySQL or die
// and display an error.
$link = mysql_connect($host, $username, $password);
if (!$link) {
die('Could not connect: ' . mysql_error());
}

// Select your database
mysql_select_db ($database);

if(isset($_GET['image_id'])) {
$sql = "SELECT imageType,imageData FROM output_images WHERE imageId=" . $_GET['image_id'];
$result = mysql_query("$sql") or die("<b>Error:</b> Problem on Retrieving Image BLOB<br/>" . mysql_error());
$row = mysql_fetch_array($result);
header("Content-type: " . $row["imageType"]);
echo $row["imageData"];
}
mysql_close($link);
?>