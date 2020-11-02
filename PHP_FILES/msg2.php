<?php
$servername="localhost";
 $user="root";
 $password="";
 $dbname = "test_database";
 $conn=mysqli_connect($servername,$user,$password,$dbname);
 if(!$conn)
 {
   die("failed to connect".mysqli_connect_error());
 }
 else {
   echo "connected successfully <br>";
 }
 $sql="SELECT CONTACT FROM station1 WHERE AREA_ASSIGNED='VIKHROLI' AND TOILET_ASSIGNED='TOILET-1'";
 $result = mysqli_query($conn, $sql);

 if (mysqli_num_rows($result) > 0) {
     // output data of each row
     $row1=mysqli_fetch_row($result);
 } 
 

mysqli_close($conn);
$msg="Plzz clean the toilet, it's stinking ";
//Your authentication key
$authKey = "25E17262B63CBD";

//Multiple mobiles numbers separated by comma
$mobileNumber = $row1[0];

//Sender ID,While using route4 sender id should be 6 characters long.
$senderId = "TEXTSM";

//Your message to send, Add URL encoding here.
$message = urlencode($msg);

//Define route 
$route = "415";
//Prepare you post parameters
$postData = array(
    'key' => $authKey,
    'routeid' => $route,
    'contacts' => $mobileNumber,
    'senderid' => $senderId,
    'msg' => $message
);

//API URL
$url="http://sms.swapneal.co.in/app/smsapi/index.php";

// init the resource
$ch = curl_init($url);
curl_setopt_array($ch, array(
    CURLOPT_URL => $url,
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_POST => true,
    // CURLOPT_POSTFIELDS => $postdata
    CURLOPT_POSTFIELDS => "key=25E17262B63CBD&routeid=415&type=text&contacts=$row1[0]&senderid=TEXTSM&msg=Please+Toilet+dho+lo"
    //,CURLOPT_FOLLOWLOCATION => true
));
//http://sms.swapneal.co.in/app/smsapi/index.php?key=25E17262B63CBD&routeid=415&type=text&contacts=&senderid=TEXTSM&msg=Hello+People%2C+have+a+great+day

//Ignore SSL certificate verification
curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);


//get response
$output = curl_exec($ch);

//Print error if any
if(curl_errno($ch))
{
    echo 'error:' . curl_error($ch);
}
else
{
    echo 'Your msg has been sent '.$output;
}
curl_close($ch);

//  mysqli_close($conn);


 ?>