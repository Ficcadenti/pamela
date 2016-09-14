      <script type="text/javascript">
          function downloadRoot()
          {
                var root_file=$("input[id='root_file']").val();
                if(root_file==="") 
                {
                    alert("Insert Output ROOT file!!!!")
                }
                else
                {
                    location.href="./dati/files/"+root_file;
                }
          };

         function showRoot()
          {
                var root_file=$("input[id='root_file']").val();
                if(root_file==="") 
                {
                    alert("Insert Output ROOT file!!!!");
                }
                else
                {
                    window.open("components/drawroot.php?file=../dati/files/"+root_file+"&nobrowser&item=Histogram%20hnorm;1&opt=colz","_blank");
                }
          };

          function getStatus()
          {
                
                var ajax = assegnaXMLHttpRequest();
                var data_post= "";

                if(ajax) 
                  {
                   // chiamata AJAX
                   $.ajax({
                     url: 'components/getstatus.php',
                     type: 'POST',
                     data: data_post,
                     success: function(res)
                     {
                        var value = JSON.parse(res);
                        if(value.status==2)
                        {
                          $("#btnShow").removeClass("disabled");
                          $("#btnDownload").removeClass("disabled");

                          $("#loading").fadeOut(800,function()
                           {
                             $("#loading").remove();
                           });

                          $("#regok").fadeOut(800,function()
                           {
                             $("#regok").remove();
                           });

                          stopGetStatus();
                        }
                        else
                        {
                          $("#btnShow").addClass("disabled");
                          $("#btnDownload").addClass("disabled");
                        }
                     }
                   });
                  }

          };

          var myInterval;

          function setStatusInterval()
          {
              myInterval=setInterval(getStatus, 5000);
              alert("setStatusInterval");
          };


          function stopGetStatus() 
          {
              clearInterval(myInterval);
              alert("stopGetStatus");
          };

          function lanciaQuery()
          {
              var $tab = $('#myTabContent'), $active = $tab.find('.tab-pane.active'), text = $active.find('#tabSelect').text();
              

              var root_file=$("input[id='root_file']").val();
              var mongo_query=$("textarea[id='mongoQuery']").val();
              var tab_select=0;

              var flag=0;


              if(root_file==="") /* variabile comune */
              {
                  alert("Insert Output ROOT file!!!!")
                  flag=1;
              }

              if(text==="beginner") /* Modalita semplificata */
              {
                    tab_select=0;
              }
              else if(text==="expert") /* Modalità esperta, l'utente inserisce la query mongo */
              {

                  if(mongo_query==="")
                  {
                      alert("Insert Mongo Query!!!!")
                      flag=1;
                  }
                  tab_select=1;
              }

              if(flag==0)
              {
                  $("#regok").remove();
                  $("#exec_query").append('<img src="media/loading.gif" alt="loading" id="loading" >');

                  var ajax = assegnaXMLHttpRequest();
                  var data_post= "";

                  if(tab_select==0) /* Modalita semplificata */
                  {
                      data_post=  "root_file="+root_file+
                              "&tab_select="+tab_select;
                  }
                  else /* Modalità esperta, l'utente inserisce la query mongo */
                  {
                      data_post=  "root_file="+root_file+
                              "&tab_select="+tab_select+
                              "&mongo_query="+mongo_query;                    
                  }

                  if(ajax) 
                  {
                   // chiamata AJAX
                   $.ajax({
                     url: 'components/pamelamongodev.php',
                     type: 'POST',
                     data: data_post,
                     success: function(res)
                     {
                       /*$("#loading").fadeOut(800,function()
                       {
                         $("#loading").remove();
                         $("#exec_query").append('<p id="regok">'+res+'</p>');
                       });*/
                       $("#exec_query").append('<p id="regok">'+res+'</p>');
                     }
                   });
                  }
               }

          }

          /*$(document).ready(function(){
            $('a[data-toggle="tab"]').on('shown.bs.tab', function(e){
                var currentTab = $(e.target).text(); // get current tab
               alert(currentTab);
            });
          });*/
      </script>

<section id="parameter_root">
      <header class="header-sezione">
          <h2>Input parameters</h2>
      </header>
      <br><br>
</section>



    <ul class="nav nav-tabs">
      <li class="active"><a href="#tab-1" data-toggle="tab">Begginer Mode</a></li>
      <li><a href="#tab-2" data-toggle="tab">Exper Mode</a></li>
    </ul>

    <div id="myTabContent" class="tab-content">
       
        <div class="tab-pane fade active in" id="tab-1">
        <form class="form-inline" role="form" > 
          <p id="tabSelect" style="display: none">beginner</p>
          <p><span class="error">* Required information.</span></p>
          <?php 

            $elem=array("Time","Lat","Lon","Alt");
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
            }
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
            <div class="col-xs-6 col-sm-3">
                      <button class="btn btn-info pull-right" type="button" onclick="lanciaQuery();setStatusInterval();getStatus();">Run Query</button>
            </div>
            
            <div class="col-xs-6 col-sm-3"> 
                      <!--<a href="components/drawroot.php?file=../dati/files/default.root&nobrowser&item=Histogram%20hnorm;1&opt=colz" role="button" id="btnShow" target="_blank" class="btn btn-info pull-right disabled"  >Show Root Map</a>-->
                      <button onclick="showRoot()" id="btnShow" class="btn btn-info pull-right disabled "  >Show Root Map</button>
                      
            </div>
            
            <div class="col-xs-6 col-sm-3">
                      <!--<input type="submit" name="submit" value="Download Root File" class="btn btn-success pull-right">-->
                      <!--<a href="./dati/files/default.root" role="button" id="btnDownload" class="btn btn-success pull-right disabled " >Download Root File</a>-->
                      <button onclick="downloadRoot()" id="btnDownload" class="btn btn-success pull-right disabled " >Download Root File</button>
            </div>
        </div>

        <div id="exec_query" style="text-align:center;">
        </div>
    </div>

<br><br><br><br><br>