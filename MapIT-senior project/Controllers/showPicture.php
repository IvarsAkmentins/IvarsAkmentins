<?php 
	// Create MySQL login values and
	// set them to your login information.
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
	$alt = htmlentities($_POST['mName']);
	//$num = htmlentities($_POST['number']);
	$num = (is_numeric($_POST['number']) ? (int)$_POST['number'] :0);


	$sql = "SELECT file FROM dig_site_bootstrap WHERE dig_site_id='$alt' AND type=1 ";
	$result = mysql_query("$sql");
	header("Content-type: image");
	echo mysql_result($result, $num);
	//echo "$alt";
	mysql_close($link);
?>