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
    $cid=1;
   $sql1="SELECT * FROM college";
   $result1=mysqli_query($conn,$sql1);
   $no=mysqli_num_rows($result1);
   echo $no ."<br>";
   $sql="SELECT namec FROM college ";
   $result=mysqli_query($conn,$sql); 
   $row=mysqli_fetch_assoc($result);
    printf ("%s \n", $row['namec']);
    $nam="Comp".$cid;
    echo "<br>".$nam;
    if($cid<=$no)
    {
      $sql2="SELECT namec FROM college WHERE T_id=$cid";
      $result2=mysqli_query($conn,$sql2);
      $row1=mysqli_fetch_row($result2);
      echo "<br>".$row1[0];
      $name=$row1[0];
      echo "<br>".$name;
    }


   mysqli_close($conn);
 ?>