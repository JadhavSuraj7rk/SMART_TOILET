<?php
$servername="localhost";
 $user="root";
 $password="";
 $dbname = "toilet";
 $conn=mysqli_connect($servername,$user,$password,$dbname);
 if(!$conn)
 {
   die("failed to connect".mysqli_connect_error());
 }
 else {
   echo "connected successfully <br>";
 }
  $TOILET_ID=$_GET['ToCo_id'];
  $AIR_QUALITY=$_GET['gas'];
  $COUNT=$_GET['count1'];
  $WATER=$_GET['water'];
  $AREA=$_GET['area'];
  $COMPARTMENT=$_GET['compartment'];
  $point=$_GET['point'];
  $card=$_GET['card'];
  date_default_timezone_set("Asia/Kolkata");
  $date1=date("H:i:s");
  echo $date1."<br>";
  $timeA = '05:00:00';
  $timeB = '13:30:00';
  $timeC = '22:00:00';
  $interval = 30; // minutes
  //$inputTime = '00:45:00'; // user inputted time
  $input = new DateTime($date1);
  $begin = new DateTime($timeA);
  $begin1 = new DateTime($timeB);
  $end = new DateTime($timeC);
  if($point<0){
    $sql="INSERT INTO station1(TOILET_ID, AIR_QUALITY, COUNT, WATER, AREA, COMPARTMENT) VALUES ('$TOILET_ID','$AIR_QUALITY','$COUNT','$WATER','$AREA','$COMPARTMENT')";
    if(mysqli_query($conn, $sql)){
      echo "inserted";
    }
    else{
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
   if($AIR_QUALITY>100||$WATER=="NO") {
    if($input >= $begin && $input <= $begin1) {
      $sql="SELECT CONTACT FROM register WHERE AREA_ASSIGNED='VIKHROLI' AND TOILET_ASSIGNED='TOILET-1' AND WORKER_ID='WORKER-1'";
     $result = mysqli_query($conn, $sql);

     if (mysqli_num_rows($result) > 0) {
      // output data of each row
      $row1=mysqli_fetch_row($result);
     }
     if($AIR_QUALITY>100){
//     //API URL
     $url="http://sms.swapneal.co.in/app/smsapi/index.php";

// // init the resource
     $ch = curl_init($url);
     curl_setopt_array($ch, array(
     CURLOPT_URL => $url,
     CURLOPT_RETURNTRANSFER => true,
     CURLOPT_POST => true,
     CURLOPT_POSTFIELDS => "key=25E17262B63CBD&routeid=415&type=text&contacts=$row1[0]&senderid=TEXTSM&msg=TOILET+stinking"
     //,CURLOPT_FOLLOWLOCATION => true
    ));
// //http://sms.swapneal.co.in/app/smsapi/index.php?key=25E17262B63CBD&routeid=415&type=text&contacts=&senderid=TEXTSM&msg=Hello+People%2C+have+a+great+day

// //Ignore SSL certificate verification
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);


// //get response
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
}
   else{
      //     //API URL
     $url="http://sms.swapneal.co.in/app/smsapi/index.php";

     // // init the resource
          $ch = curl_init($url);
          curl_setopt_array($ch, array(
          CURLOPT_URL => $url,
          CURLOPT_RETURNTRANSFER => true,
          CURLOPT_POST => true,
          CURLOPT_POSTFIELDS => "key=25E17262B63CBD&routeid=415&type=text&contacts=$row1[0]&senderid=TEXTSM&msg=No+Water"
          //,CURLOPT_FOLLOWLOCATION => true
         ));
     // //http://sms.swapneal.co.in/app/smsapi/index.php?key=25E17262B63CBD&routeid=415&type=text&contacts=&senderid=TEXTSM&msg=Hello+People%2C+have+a+great+day
     
     // //Ignore SSL certificate verification
         curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
         curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
     
     
     // //get response
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
   }
   curl_close($ch); 
 }
 if($input >= $begin1 && $input <= $end) {
     $sql="SELECT CONTACT FROM register WHERE AREA_ASSIGNED='VIKHROLI' AND TOILET_ASSIGNED='TOILET-1' AND WORKER_ID='WORKER-2'";
     $result = mysqli_query($conn, $sql);

    if (mysqli_num_rows($result) > 0) {
      // output data of each row
      $row1=mysqli_fetch_row($result);
    }
    if($AIR_QUALITY>100){
   //API URL
    $url="http://sms.swapneal.co.in/app/smsapi/index.php";
 // init the resource
    $ch = curl_init($url);
    curl_setopt_array($ch, array(
     CURLOPT_URL => $url,
     CURLOPT_RETURNTRANSFER => true,
     CURLOPT_POST => true,
     CURLOPT_POSTFIELDS => "key=25E17262B63CBD&routeid=415&type=text&contacts=$row1[0]&senderid=TEXTSM&msg=TOILET+stinking"
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
}
   else{
            //     //API URL
     $url="http://sms.swapneal.co.in/app/smsapi/index.php";

     // // init the resource
          $ch = curl_init($url);
          curl_setopt_array($ch, array(
          CURLOPT_URL => $url,
          CURLOPT_RETURNTRANSFER => true,
          CURLOPT_POST => true,
          CURLOPT_POSTFIELDS => "key=25E17262B63CBD&routeid=415&type=text&contacts=$row1[0]&senderid=TEXTSM&msg=No+Water"
          //,CURLOPT_FOLLOWLOCATION => true
         ));
     // //http://sms.swapneal.co.in/app/smsapi/index.php?key=25E17262B63CBD&routeid=415&type=text&contacts=&senderid=TEXTSM&msg=Hello+People%2C+have+a+great+day
     
     // //Ignore SSL certificate verification
         curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
         curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
     
     
     // //get response
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
   }
    curl_close($ch);  
 }
  }
  }
  if($point>=0){
    $sql="INSERT INTO credit(RFID1,CREDIT) VALUES ('$card','$point')";
    if(mysqli_query($conn, $sql)){
        echo "inserted";
    }
    else{
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
  }
  mysqli_close($conn);
//  $sql="SELECT CONTACT FROM station1 WHERE AREA_ASSIGNED='VIKHROLI' AND TOILET_ASSIGNED='TOILET-1' AND WORKER_ID='WORKER-1'";
//  $result = mysqli_query($conn, $sql);

//  if (mysqli_num_rows($result) > 0) {
//      // output data of each row
//      $row1=mysqli_fetch_row($result);
//  } 
 
//$msg="Plzz clean the toilet, it's stinking ";
//Your authentication key
//$authKey = "25E17262B63CBD";

//Multiple mobiles numbers separated by comma
//$mobileNumber = $row1[0];

//Sender ID,While using route4 sender id should be 6 characters long.
//$senderId = "TEXTSM";

//Your message to send, Add URL encoding here.
//$message = urlencode($msg);

//Define route 
//$route = "415";
//Prepare you post parameters
//$postData = array(
//     'key' => $authKey,
//     'routeid' => $route,
//     'contacts' => $mobileNumber,
//     'senderid' => $senderId,
//     'msg' => $message
// );
 ?>