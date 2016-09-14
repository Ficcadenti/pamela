<div class="container">
    <section id="parameter_root">
          <header class="header-sezione">
              <h2>Input parameters</h2>
          </header>
          <br><br>
    </section>

    <ul class="nav nav-tabs">
      <li class="active"><a href="#tab-1" data-toggle="tab">Beginner Mode</a></li>
      <li><a href="#tab-2" data-toggle="tab">Expert Mode</a></li>
    </ul>

    <div id="myTabContent" class="tab-content">
       
        <div class="tab-pane fade active in" id="tab-1">
        <form class="form-inline" role="form" > 
          <p id="tabSelect" style="display: none">beginner</p>
          <p><span class="error">* Required information.</span></p>
          <?php 

            /* Get TASK PARAM */
            $id_task=13;
            // Create connection
            $conn = new mysqli($dbservername, $username, $password, $dbname);

            // Check connection
            if ($conn->connect_error) 
            {
              echo("Errore connessione mysql(pamelamongodev) !!!!");
            }
            else
            {
                $sql = "SELECT id_param,type_param,name_param_web,desc_param,tool_tip,value_min,value_max,value_len,value_placeholder,value_default FROM tab_task_param WHERE id_task=".$id_task." AND param_visible=1 order by order_param";

                $result = $conn->query($sql);

                /*
                // DEBUG SELECT
                echo "Select: ".$sql."<br>";
                echo "Row: ".$result->num_rows."<br>";
                */

                if ($result->num_rows > 0) 
                {
                  while($row = $result->fetch_assoc()) 
                  {
                        echo '
                           <div id="'.$row["name_param_web"].'_input">
                              <script type="text/javascript">
                                        function getval_'.$row["name_param_web"].'(sel) 
                                        {
                                           if(sel.value!="none")
                                            {

                                              $("#'.$row["name_param_web"].'_op3").prop("disabled", false);
                                              $("#'.$row["name_param_web"].'_max").prop("disabled", false);
                                            }else
                                            {
                                              $("#'.$row["name_param_web"].'_op3").prop("disabled", true);
                                              $("#'.$row["name_param_web"].'_max").prop("disabled", true);
                                            }
                                        };
                                        ';

                                        if($row["type_param"]==3) // 3=slide
                                        {  
                                            echo '
                                            $(function() 
                                            {
                                                $( "#slider_'.$row["name_param_web"].'_min" ).slider(
                                                  {
                                                        orientation:"horizontal",
                                                        min: '.$row["value_min"].',
                                                        max: '.$row["value_max"].',
                                                        slide: function( event, ui ) {
                                                        $( "#'.$row["name_param_web"].'_min" ).val( ui.value );
                                                  }  
                                                });
                                                $( "#'.$row["name_param_web"].'_min" ).val( $( "#slider_'.$row["name_param_web"].'_min" ).slider( "value" ) );

                                                $( "#slider_'.$row["name_param_web"].'_max" ).slider(
                                                  {
                                                        orientation:"horizontal",
                                                        min: '.$row["value_min"].',
                                                        max: '.$row["value_max"].',
                                                        slide: function( event, ui ) {
                                                        $( "#'.$row["name_param_web"].'_max" ).val( ui.value );
                                                  }  
                                                });
                                                $( "#'.$row["name_param_web"].'_max" ).val( $( "#slider_'.$row["name_param_web"].'_max" ).slider( "value" ) );
                    
                                            });';
                                         };

                        echo '
                              </script>

                              <input id="'.$row["name_param_web"].'box" type="checkbox"  data-toggle="collapse" data-target="#'.$row["name_param_web"].'">
                              <label for="'.$row["name_param_web"].'box">'.$row["desc_param"].'</label><span class="question"><p>'.$row["tool_tip"].'</p></span>
                              <div id="'.$row["name_param_web"].'" class="collapse">

                              <select class = "form-control" id="'.$row["name_param_web"].'_op1">
                                <option>></option>
                                <option>>=</option>
                                <option><</option>
                                <option><=</option>
                                <option>==</option>
                                <option>!=</option>
                              </select>

                              <div class="form-group">
                                <input type="text" class="numeric form-control" id="'.$row["name_param_web"].'_min" maxlength="'.$row["value_len"].'" size="'.$row["value_len"].'" placeholder="'.$row["value_placeholder"].'"';

                          if($row["value_placeholder"]=="")
                            echo ' value="'.$row["value_default"].'"';

                          echo'>
                              </div>
                              ';

                              if($row["type_param"]==3)
                              {
                                  echo '<div class="form-group" id="slider_'.$row["name_param_web"].'_min" style="width:100px;margin-right:20px;margin-left:5px"></div>';
                              }

                              echo '
                              <select class = "form-control" id="'.$row["name_param_web"].'_op2" onchange="getval_'.$row["name_param_web"].'(this);">
                                <option>none</option>
                                <option>AND</option>
                                <option>OR</option>
                              </select>

                              <select class = "form-control" id="'.$row["name_param_web"].'_op3" disabled>
                                  <option>></option>
                                  <option>>=</option>
                                  <option><</option>
                                  <option><=</option>
                                  <option>==</option>
                                  <option>!=</option>
                                </select>

                              <div class="form-group">
                                <input type="text" class="form-control" id="'.$row["name_param_web"].'_max" maxlength="'.$row["value_len"].'" size="'.$row["value_len"].'" placeholder="'.$row["value_placeholder"].'" disabled';
                          if($row["value_placeholder"]=="")
                            echo ' value="'.$row["value_default"].'"';

                          echo '>
                              </div>

                              ';

                              if($row["type_param"]==3)
                              {
                                  echo '<div class="form-group" id="slider_'.$row["name_param_web"].'_max" style="width:100px;margin-right:20px;margin-left:5px"></div>';
                              }

                              echo '
                              <select class = "form-control" id="'.$row["name_param_web"].'_op4">
                                <option>none</option>
                                <option>AND</option>
                                <option>OR</option>
                              </select>
                          </div>
                        </div>
                      ';
                    }
                }
                else 
                {
                   echo "DB empty!!!!!";
                }
            }

            $conn->close();

            /*$elem=array("Time","Lat","Lon","Alt");
            $elemSlide=array(0,1,1,0);
            $elemSlideMin=array(0,-90,-180,0);
            $elemSlideMax=array(0,90,180,0);
            $elemPlaceholder=array("2000-10-06 19:00:00","","","");
            $elemDefaultVal=array("","0","0","0");
            $elemMaxLength=array(19,3,4,5);
            $elemDesc=array("Time (GMT)","Latitude","Longitude","Altitude");
            $elemToolTip=array("Enter the time intervals with any conditions.","Enter the latitude intervals with any conditions.<br>Latitudes range from -90 to 90.","Enter the longitude intervals with any conditions.<br>Longitudes range from -180 to 180.","Enter the altitude intervals with any conditions.");
            $arrlength=count($elem);

            for($x=0;$x<$arrlength;$x++)
            {
                echo '
                   <div id="'.$elem[$x].'_input">
                      <script type="text/javascript">
                                function getval_'.$elem[$x].'(sel) 
                                {
                                   if(sel.value!="none")
                                    {

                                      $("#'.$elem[$x].'_op3").prop("disabled", false);
                                      $("#'.$elem[$x].'_max").prop("disabled", false);
                                    }else
                                    {
                                      $("#'.$elem[$x].'_op3").prop("disabled", true);
                                      $("#'.$elem[$x].'_max").prop("disabled", true);
                                    }
                                };
                                ';

                                if($elemSlide[$x]==1)
                                {  
                                    echo '
                                    $(function() 
                                    {
                                        $( "#slider_'.$elem[$x].'_min" ).slider(
                                          {
                                                orientation:"horizontal",
                                                min: '.$elemSlideMin[$x].',
                                                max: '.$elemSlideMax[$x].',
                                                slide: function( event, ui ) {
                                                $( "#'.$elem[$x].'_min" ).val( ui.value );
                                          }  
                                        });
                                        $( "#'.$elem[$x].'_min" ).val( $( "#slider_'.$elem[$x].'_min" ).slider( "value" ) );

                                        $( "#slider_'.$elem[$x].'_max" ).slider(
                                          {
                                                orientation:"horizontal",
                                                min: '.$elemSlideMin[$x].',
                                                max: '.$elemSlideMax[$x].',
                                                slide: function( event, ui ) {
                                                $( "#'.$elem[$x].'_max" ).val( ui.value );
                                          }  
                                        });
                                        $( "#'.$elem[$x].'_max" ).val( $( "#slider_'.$elem[$x].'_max" ).slider( "value" ) );
            
                                    });';
                                 };

                echo '
                      </script>

                      <input id="'.$elem[$x].'box" type="checkbox"  data-toggle="collapse" data-target="#'.$elem[$x].'">
                      <label for="'.$elem[$x].'box">'.$elemDesc[$x].'</label><span class="question"><p>'.$elemToolTip[$x].'</p></span>
                      <div id="'.$elem[$x].'" class="collapse">

                      <select class = "form-control" id="'.$elem[$x].'_op1">
                        <option>></option>
                        <option>>=</option>
                        <option><</option>
                        <option><=</option>
                        <option>==</option>
                        <option>!=</option>
                      </select>

                      <div class="form-group">
                        <input type="text" class="form-control" id="'.$elem[$x].'_min" maxlength="'.$elemMaxLength[$x].'" size="'.$elemMaxLength[$x].'" placeholder="'.$elemPlaceholder[$x].'"';

                  if($elemPlaceholder[$x]=="")
                    echo ' value="'.$elemDefaultVal[$x].'"';

                  echo'>
                      </div>
                      ';

                      if($elemSlide[$x]==1)
                      {
                          echo '<div class="form-group" id="slider_'.$elem[$x].'_min" style="width:100px;margin-right:20px;margin-left:5px"></div>';
                      }

                      echo '
                      <select class = "form-control" id="'.$elem[$x].'_op2" onchange="getval_'.$elem[$x].'(this);">
                        <option>none</option>
                        <option>AND</option>
                        <option>OR</option>
                      </select>

                      <select class = "form-control" id="'.$elem[$x].'_op3" disabled>
                          <option>></option>
                          <option>>=</option>
                          <option><</option>
                          <option><=</option>
                          <option>==</option>
                          <option>!=</option>
                        </select>

                      <div class="form-group">
                        <input type="text" class="form-control" id="'.$elem[$x].'_max" maxlength="'.$elemMaxLength[$x].'" size="'.$elemMaxLength[$x].'" placeholder="'.$elemPlaceholder[$x].'" disabled';
                  if($elemPlaceholder[$x]=="")
                    echo ' value="'.$elemDefaultVal[$x].'"';

                  echo '>
                      </div>

                      ';

                      if($elemSlide[$x]==1)
                      {
                          echo '<div class="form-group" id="slider_'.$elem[$x].'_max" style="width:100px;margin-right:20px;margin-left:5px"></div>';
                      }

                      echo '
                      <select class = "form-control" id="'.$elem[$x].'_op4">
                        <option>none</option>
                        <option>AND</option>
                        <option>OR</option>
                      </select>
                  </div>
                </div>
              ';
            }*/
          ?>
          <!--<div class="form-group">
              <label for="InputName">Output ROOT file</label><span class="error" style="color:red;font-weight:bold"> *</span><span class="question"><p>Insert name of generated root file.</p></span>
              <input type="text" class="form-control" id="root_file" maxlength="100" size="100" value="<?php echo $name;?>">
          </div>-->
          <br><br>
          </form>
        </div>

        <div class="tab-pane fade" id="tab-2">
          <p id="tabSelect" style="display: none">expert</p>
          <p><span class="error">* Required information.</span></p>
          <div class="form-group">
              <label for="comment">Mongo Query</label><span class="error" style="color:red;font-weight:bold"> *</span><span class="question"><p>Insert Mongo Query.<br>Es.: {abstime: {$gt: 0} }</p></span>
              <textarea class="form-control" rows="5" id="mongoQuery" placeholder="{abstime: {$gt: 0} }"></textarea>
              <!--<label for="InputName">Output ROOT file</label><span class="error" style="color:red;font-weight:bold"> *</span><span class="question"><p>Insert name of generated root file.</p></span>
              <input type="text" class="form-control" id="root_file" maxlength="100" size="100" value="<?php echo $name;?>">-->
          </div>
        </div>

        <div class="form-group">
             <label for="InputName">Output ROOT file</label><span class="error" style="color:red;font-weight:bold"> *</span><span class="question"><p>Insert name of generated root file.</p></span>
            <input type="text" class="form-control" id="root_file" maxlength="100" size="100" value="<?php echo $name;?>">
        </div>

        <br>

        <div class="row">
            <div class="col-xs-6 col-sm-3 centrato">
                      <button class="btn btn-info pull-right" type="button" onclick="lanciaQuery();setStatusInterval();getStatus();">Run Query</button>
            </div>
        </div>

        <div id="exec_query" style="text-align:center;">
        </div>
    </div>

</div> <!-- /container -->


<script type="text/javascript">
  $(".numeric").numeric({ decimal : "," });
  $(".integer").numeric(false, function() { alert("Integers only"); this.value = ""; this.focus(); });
  $(".positive").numeric({ negative: false }, function() { alert("No negative values"); this.value = ""; this.focus(); });
  $(".positive-integer").numeric({ decimal: false, negative: false }, function() { alert("Positive integers only"); this.value = ""; this.focus(); });
    $(".decimal-2-places").numeric({ decimalPlaces: 2 });
  $("#remove").click(
    function(e)
    {
      e.preventDefault();
      $(".numeric,.integer,.positive,.positive-integer,.decimal-2-places").removeNumeric();
    }
  );
  </script>
