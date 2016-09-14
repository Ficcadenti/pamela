<div class="container">

    <section id="output_root">
          <header class="header-sezione">
              <h2>My root files</h2>
          </header>
    </section>


    <div class="panel-carousel">  
        <div class="row">
            <div class="col-xs-6 col-sm-3 form-group ">
                <label for="InputName">ROOT file</label><span class="question"><p>List root file.</p></span>
                <select class = "form-control" id="listRootFile" style="width:200px">
                <?php
                    $d = dir("./dati/files/");
                    $cont=0;
                    while (false !== ($entry = $d->read())) 
                    {
                      if(($entry!=".")&&($entry!=".."))
                      {
                        echo "<option>".$entry."</option>";
                      }
                    }
                    $d->close();
                ?>
                </select>
            </div>

                

            <div class="col-xs-6 col-sm-3"> 
                      <!--<a href="components/drawroot.php?file=../dati/files/default.root&nobrowser&item=Histogram%20hnorm;1&opt=colz" role="button" id="btnShow" target="_blank" class="btn btn-info pull-right disabled"  >Show Root Map</a>-->
                      <br>
                      <button onclick="showRoot()" id="btnShow" class="btn btn-info pull-right"  >Show Root Map</button> 
            </div>
            
            <div class="col-xs-6 col-sm-3">
                      <!--<input type="submit" name="submit" value="Download Root File" class="btn btn-success pull-right">-->
                      <!--<a href="./dati/files/default.root" role="button" id="btnDownload" class="btn btn-success pull-right disabled " >Download Root File</a>-->
                      <br>
                      <button onclick="downloadRoot()" id="btnDownload" class="btn btn-success pull-right" >Download Root File</button>
            </div> 

            <div class="col-xs-6 col-sm-3">
                      <!--<input type="submit" name="submit" value="Download Root File" class="btn btn-success pull-right">-->
                      <!--<a href="./dati/files/default.root" role="button" id="btnDownload" class="btn btn-success pull-right disabled " >Download Root File</a>-->
                      <br>
                      <button onclick="deleteRoot()" type="button" id="btnDownload" class="btn btn-danger pull-right" data-toggle="modal" data-target="#myModal">Delete Root File</button>
            </div> <!-- /col-xs-6 col-sm-3 -->          
        </div> <!-- /row -->
    </div> <!-- /panel-carousel -->

    <!-- Modal -->
    <div class="modal fade" id="myModal" role="dialog">
      <div class="modal-dialog">
      
        <!-- Modal content-->
        <div class="modal-content">
          <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal">&times;</button>
            <h4 id="rotFileDelete" class="modal-title" >Delete 'default.root'</h4>
          </div>
          <div class="modal-body">
            <p>Do you want delete this file? </p>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-danger ripple-effect btn-vote" data-dismiss="modal"> Yes</button>
            <button type="button" class="btn btn-success ripple-effect btn-vote" data-dismiss="modal"> No</button>
          </div>
        </div>
        
      </div>
    </div> <!-- /Modal -->

</div> <!-- /container -->



