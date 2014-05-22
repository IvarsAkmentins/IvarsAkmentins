<?php
if (!isset($_SESSION)) {
    session_start();
}
ob_start();

//redirects back to main page in case there is no user
if (!isset($_SESSION['userid']) || $_SESSION['userid'] < 0) {
    header('Location: http://www.mocivilwar.org');
}

date_default_timezone_set('UTC');



//$alt = htmlentities($_POST['mName']);

//$sql = "SELECT file FROM dig_site_bootstrap WHERE type=1";
//$result = mysql_query("$sql");
//header("Content-type: image/jpeg");
//echo mysql_result($result, 0);
//mysql_close($_SESSION);

//$sql = "SELECT file FROM dig_site_bootstrap WHERE type=1";
//$count= mysql_query("$sql");

//$gotten = @mysql_query("select file from dig_site_bootstrap WHERE type=2");
//$row = @mysql_fetch_assoc($gotten);
//$bytes = $row[imgdata];
//header("Content-type: application/pdf");
//header('Content-disposition: attachment; filename="thing.pdf"');
//print $bytes;

?>

<!doctype html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <script src="../libraries/jquery-1.11.0.js"></script>
        <link rel="stylesheet" href="../libraries/jquery-ui-1.9.2.custom/css/redmond/jquery-ui-1.9.2.custom.css" />
        <script src="../libraries/jquery-ui-1.9.2.custom/js/jquery-ui-1.9.2.custom.js"></script>
        <script src="../libraries/jquery-ui-1.9.2.custom/js/jquery-ui-1.9.2.custom.min.js"></script>
        <script src="../js/DateFormat.js"></script>
   
        <link rel="stylesheet" href="../libraries/css/primary.css" />

        <title>MapIT - Manage User</title>
        
        <script src="../js/Main.js"></script>
    </head>

    <body>
        <div id="header">
            <div style="width: 100%"><img src="../libraries/images/header-blue-bar.gif" id="image_title" width=100%> </div>
            <div style="position: relative"><img src="../libraries/images/MapIT_Title.png" id="image_title" class="title_image"></div>
            <div align="right" style="position: relative">
                <span class="title_text">Missouri's Civil War Dig Sites <br>
                    User Name: <?php echo $_SESSION['username']; ?> - Date: <?php echo date('m/d/Y', time() - 5 * 60 * 60); ?>
                </span>
            </div>
        </div> 

        <div align="right" id="admin_head">  
            <div id="admin_manager_div" class="admin_head_child" style="padding-right: 15px">
                <button id="map_view_btn" class="menu_btn">Map</button>
                <div class="menu_labels" style="margin-left: 7px">
                    <label>Dig Sites</label><br>
                    <label>Map</label>
                </div>
            </div> 
            <div id="admin_manager_div" class="admin_head_child" style="padding-right: 15px <?php echo ($_SESSION['userstatus'] < 1) ? ';display:none' : '' ?>" >
                <button id="admin_manager_btn" class="menu_btn">Admin Manager</button>
                <div class="menu_labels" style="margin-left: 7px">
                    <label>Admin</label><br>
                    <label>Manager</label>
                </div>
            </div>           
            <div id="dig_list_div" class="admin_head_child" style="padding-right: 15px">
                <button id="dig_list_btn" class="menu_btn">Dig Sites Archive</button>
                <div class="menu_labels" style="margin-left: 7px">
                    <label>Dig Sites</label><br>
                    <label>Archive</label>
                </div>
                
            </div>
            <div id="logout_div" class="admin_head_child" style="<?php echo ($_SESSION['userstatus'] < 1) ? 'display:none' : '' ?>">
                <button id="logout_btn" class="menu_btn">Logout</button>
                <div class="menu_labels" style="margin-left: 11px">
                    <label>Logout</label>
                </div>
            </div>
        </div>
        
        <div style="border-top: 1px solid gray; margin-top: 100px"></div>
        <div id="body" style="margin-left: 350px"> 
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
	?><h2><?php echo "$alt" ?></h2><?php
	$result = mysql_query("select count(1) FROM dig_site_bootstrap WHERE dig_site_id='$alt' AND type=1");
	$row = mysql_fetch_array($result);

	$total = $row[0];
	echo "Total Pictures: " . $total;
	?><br><?php
	for($i=0; $i<$total;$i++)
	{ 
	?>
	<div style="width:400px;">
		<div style="float: left; width: 130px"> 
		<form action="../Controllers/showPicture.php" method="POST" target="_blank">
		<input type="text" style="display:none;" name="mName" value="<?php echo "$alt" ?>"/>
		<input type="number" style="display:none;" name="number" value= "<?php echo "$i" ?>"/>
		<?php
		$k=$i+1;
		echo "#$k";?>
		<input type="submit" value="See Picture" />
		</form>
		</div>
		<div style="float: right; width: 225px"> 
		<form action="../Controllers/deletePicture.php" method="POST" target="_blank">
		<input type="text" style="display:none;" name="mName" value="<?php echo "$alt" ?>"/>
		<input type="number" style="display:none;" name="number" value= "<?php echo "$i" ?>"/>
		<input type="submit" value="Delete" />
		</form>
		</div>
	</div>
		<?php
	}
	$result = mysql_query("select count(1) FROM dig_site_bootstrap WHERE dig_site_id='$alt' AND type=2");
	$row = mysql_fetch_array($result);

	$total = $row[0];
	echo "Total Files: " . $total;
	
	for($i=0; $i<$total;$i++)
	{
		?>
		<div style="width:400px;">
		<div style="float: left; width: 130px"> 
		<p><form action="../Controllers/downloadFile.php" method="POST" target="_blank">
		<input type="text" style="display:none;" name="mName" value="<?php echo "$alt" ?>"/>
		<input type="text" style="display:none;" name="number" value="<?php echo "$i" ?>"/>
		<?php
		$k=$i+1;
		echo "#$k";?>
		<input type="submit" value="Download" /></p>
		</form>
		</div>
		<div style="float: right; width: 225px"> 
		<p><form action="../Controllers/deletePicture.php" method="POST" target="_blank">
		<input type="text" style="display:none;" name="mName" value="<?php echo "$alt" ?>"/>
		<input type="number" style="display:none;" name="number" value= "<?php echo "$i" ?>"/>
		<input type="submit" value="Delete" />
		</form>
		</div>
	</div>
		<?php	
	}

	mysql_close($link);
	
	 ?>
        

        </div>

        <div id="footer" style="margin-top: 40px">
            <div style="border-top: 1px solid gray">
                <p class="text_footer">&copy;&nbsp;Copyright 2014 MapIT Team</p>
            </div>
        </div>

        <div id="dialog"></div>
    </body>
</html>