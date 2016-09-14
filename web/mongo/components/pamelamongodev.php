<?php
         include ("../config/configure.php");

         // definizione variabili e set a ""

         if ( isset($_POST["tab_select"]) )
         {
            $tab_select = $_POST["tab_select"];
         }

         if ( isset($_POST["root_file"]) ) /* variabile comune */
         {
            $root_file = $_POST["root_file"];
         }

         if($tab_select==0) /* Modalita semplificata */
         {

         }
         else if($tab_select==1) /* Modalità esperta, l'utente inserisce la query mongo */
         {
               if ( isset($_POST["mongo_query"]) )
               {
                  $mongo_query = $_POST["mongo_query"];
               }
         }

         
         


         // Create connection
         $conn = new mysqli($dbservername, $username, $password, $dbname);

         // Check connection
         if ($conn->connect_error) 
         {
            echo("Errore connessione mysql(pamelamongodev) !!!!");
         }
         else
         {

            if($tab_select==0) /* Modalita semplificata */
            {
               $query="update tab_pipeline set status=6,root_file='".$root_file."' where id=5";  
            }
            else if($tab_select==1) /* Modalità esperta, l'utente inserisce la query mongo */
            {
               $query="update tab_pipeline set status=6,root_file='".$root_file."',query_mongo='".$mongo_query."' where id=5";
            }

            $st=$conn->stmt_init();

            if($st->prepare($query))
            {
               $st->execute();
               echo "The query was sent, wait a moment for the results .....";
            }
            else
            {
               echo "Errore update task !!!";
               echo "<br>";
               echo $query;
            }
         }
?>