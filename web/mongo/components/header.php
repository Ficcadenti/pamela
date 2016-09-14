<!-- 
**************************************************************************
  (c) Raffaele Ficcadenti 
  Maggio 2016
  raffaele.ficcadenti@gmail.com

  File:   header.php
  Descr:  Classe header contenente la barra di navigazione con i menu.
************************************************************************** 
-->
<header id="main-menu">
    <nav class="navbar navbar-default">

      <div class="container">
       
        <div class="navbar-header">
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-responsive-collapse">
                 <span class="icon-bar"></span>
                 <span class="icon-bar"></span>
                 <span class="icon-bar"></span>
            </button>
          <a class="navbar-brand">Prototype Pamela Mongo/ROOT</a>
        </div>

        <div class="collapse navbar-collapse navbar-responsive-collapse">
            <ul class="nav navbar-nav">
                    <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown">Home <span class="caret"></span></a>
                     <ul class="dropdown-menu" id="selectLang">
                      <li><a href=<?php echo "'".$local_host."?lang=".$lang."'"; ?>>Home</a></li>
                     </ul>
                    </li>
              </ul>
        </div><!-- /collapse -->
      </div><!-- /container -->
    </nav><!-- /navbar -->
</header>