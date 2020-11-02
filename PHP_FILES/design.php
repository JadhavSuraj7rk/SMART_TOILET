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
    $cid=3;
   $sql1="SELECT * FROM college";
   $result1=mysqli_query($conn,$sql1);
   $no=mysqli_num_rows($result1);
   echo $no ."<br>";
   $sql="SELECT namec FROM college ";
   if($result=mysqli_query($conn,$sql)) {
   while($row=mysqli_fetch_assoc($result)){
    printf (" %s \n", $row['namec']);
     }
     mysqli_free_result($result);
    }
   
    if($cid<=$no)
     {
      $sql2="SELECT namec FROM college WHERE T_id=$cid";
      $result2=mysqli_query($conn,$sql2);
      $row1=mysqli_fetch_assoc($result2);
      echo "<br>".$row1['namec'];
      $nam1=$row1['namec'];
      echo "<br>".$nam1;
      $sqlinsert = "INSERT INTO $nam1 (name1, city, percentile)
                    VALUES ('Swam','Mumbai','95')";

       if (mysqli_query($conn, $sqlinsert)) {
         echo "New record inserted successfully";
         } else {
         echo "Error: " . $sqlinsert . "<br>" . mysqli_error($conn);
        }
     }
    else
     {
        $nam="Comp".$cid;
        echo "<br>".$nam;
        $sqlcreate="CREATE TABLE $nam (
                   Id INT (5) AUTO_INCREMENT PRIMARY KEY,
                   name1 VARCHAR (10),
                   city VARCHAR (10),
                   percentile INT (5),
                   time1 TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP)
                   ";
        if (mysqli_query($conn, $sqlcreate)) {
            echo "Table  created successfully";
        } else {
            echo "Error creating table: " . mysqli_error($conn);
        } 
        $sqlinsert = "INSERT INTO $nam (name1, city, percentile)
                    VALUES ('Swat','Indigo','93')";

       if (mysqli_query($conn, $sqlinsert)) {
         echo "New record inserted successfully";
         } else {
         echo "Error: " . $sqlinsert . "<br>" . mysqli_error($conn);
        }
        $sqlinsertcol = "INSERT INTO college (namec)
                    VALUES ('$nam')";

       if (mysqli_query($conn, $sqlinsertcol)) {
         echo "New record inserted successfully";
         } else {
         echo "Error: " . $sqlinsertcol . "<br>" . mysqli_error($conn);
        }


     }

   mysqli_close($conn);
 ?>