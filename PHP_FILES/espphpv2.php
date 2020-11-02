<?php
   $servername="localhost";
   $user="root";
   $password="";
   $dbname = "test_database";
   $conn=mysqli_connect($servername,$user,$password,$dbname);
   //$name=$_GET["name1"];
   //$city= $_GET["city"];
   //$percentile= $_GET["percentile"];
   if(!$conn)
   {
     die("failed to connect".mysqli_connect_error());
   }
   else {
     echo "connected successfully <br>";
   }

  //if(!empty($_GET['name1'])&&!empty($_GET['city'])&&!empty($_GET['percentile']))
  //{
      $name1=$_GET['name1'];
      $city=$_GET['city'];
      $percentile=$_GET['percentile'];
      $cid=$_GET['cid'];
      
      
      //if(isset($cid)){
      //  switch($cid){
        //  case $cid=A:
          //       $sql1="INSERT INTO student(name1, city, percentile) VALUES ('$name1','$city','$percentile')";
            //     mysqli_query($conn, $sql1);
              //  
                //break;
         // case $cid=B:
           //     $sql2="INSERT INTO teachers(name1, city, percentile) VALUES ('$name1','$city','$percentile')";
             //   mysqli_query($conn, $sql2);
                
               // break;
      //}
      //}

     if($cid==1){
        $sql1="INSERT INTO student(name1, city, percentile) VALUES ('$name1','$city','$percentile')";
        mysqli_query($conn, $sql1);
       }
       else{
        $sql2="INSERT INTO teachers(name2, city1, percentile1) VALUES ('$name1','$city','$percentile')";
        mysqli_query($conn, $sql2);
       }




      //if(mysqli_query($conn, $sql)==TRUE)
      //{
      //    echo "New record created successfully";
    //  } else
    //   {
      //    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    //  }
      // ********************************
 // }
   //if (isset($name)){
  // $fired=mysqli_query($conn, "INSERT INTO student (city,percentile) VALUES ('$city','$percentile')");}
   //if ($fired) {
   //echo "New record created successfully";
   //}
   //else{
   //echo "Error: "."<br>".mysqli_error($conn);
   //}

   mysqli_close($conn);
  ?>