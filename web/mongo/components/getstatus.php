<?php
         include ("../config/configure.php");

         // definizione variabili e set a ""
         $status=0;
         $root_file="";
         $value = null;

         // Create connection
         $conn = new mysqli($dbservername, $username, $password, $dbname);

         // Check connection
         if ($conn->connect_error) 
         {
            echo("Errore connessione mysql(pamelamongodev) !!!!");
         }
         else
         {

               $sql = "SELECT status,root_file FROM tab_pipeline WHERE id=5";
               $result = $conn->query($sql);

               if ($result->num_rows > 0) 
               {
                  while($row = $result->fetch_assoc()) 
                  {

                     $status = $row["status"];
                     $root_file = $row["root_file"];

                     $value = array( 'status' => ($status),
                                     'root_file' => ($root_file) );
                  }
               }
               else 
               {
                   echo "DB empty!!!!!";
               

               }
         }

         echo json_encode($value,JSON_PRETTY_PRINT);

         $conn->close();
?>