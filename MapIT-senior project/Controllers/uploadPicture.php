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

// Make sure the user actually
// selected and uploaded a file
if (isset($_FILES['image']) && $_FILES['image']['size'] > 0) {

// Temporary file name stored on the server
$tmpName = $_FILES['image']['tmp_name'];

// Read the file
$fp = fopen($tmpName, 'r');
$data = fread($fp, filesize($tmpName));
$data = addslashes($data);
$alt = htmlentities($_POST['mName']);

fclose($fp);

// Create the query and insert
// into our database.
$query = "INSERT INTO dig_site_bootstrap ";
$query .= "(dig_site_id, type, file) VALUES ('$alt','1','$data')";
$results = mysql_query($query, $link);

// Print results
print "Thank you, your image has been uploaded.";
?>
<script type="text/javascript">
parent.document.getElementById("message").innerHTML="Image is uploaded";
</script>
<?php

}
else {
print "No image selected/uploaded";
?>
<script type="text/javascript">
parent.document.getElementById("message").innerHTML="Image Size is too big";
</script>
<?php
}

if (isset($_FILES['userfile']) && $_FILES['userfile']['size'] > 0) {

// Temporary file name stored on the server
$tmpName = $_FILES['userfile']['tmp_name'];

// Read the file
$fp = fopen($tmpName, 'r');
$data = fread($fp, filesize($tmpName));
$data = addslashes($data);
$alt = htmlentities($_POST['mName']);
fclose($fp);


// Create the query and insert
// into our database.
$query = "INSERT INTO dig_site_bootstrap ";
$query .= "(dig_site_id, type, file) VALUES ('$alt','2','$data')";
$results = mysql_query($query, $link);
print "Thank you, your file has been uploaded.";
?>
<script type="text/javascript">
parent.document.getElementById("message2").innerHTML="File is Uploaded";
</script>
<?php
}
else {print "No file selected/uploaded";
?>
<script type="text/javascript">
parent.document.getElementById("message2").innerHTML="File Size is too big";
</script>
<?php
}

// Close our MySQL Link
mysql_close($link);
?>