CREATE DATABASE  IF NOT EXISTS `pamelamongodev` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `pamelamongodev`;

-- MySQL dump 10.13  Distrib 5.7.9, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: pamelamongodev
-- ------------------------------------------------------
-- Server version	5.7.10-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tab_error_lib`
--

DROP TABLE IF EXISTS `tab_error_lib`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_error_lib` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_error` varchar(45) DEFAULT NULL,
  `error_desc` varchar(400) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_error_lib`
--

LOCK TABLES `tab_error_lib` WRITE;
/*!40000 ALTER TABLE `tab_error_lib` DISABLE KEYS */;
INSERT INTO `tab_error_lib` VALUES (1,'1','Task without user'),(2,'2','Task without pipeline'),(3,'3','Task running for more than N days'),(4,'4','Task stalled for more than N days'),(5,'0','Task Ok');
/*!40000 ALTER TABLE `tab_error_lib` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_operators_lib`
--

DROP TABLE IF EXISTS `tab_operators_lib`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_operators_lib` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_opt` int(11) DEFAULT NULL,
  `name_opt` varchar(45) DEFAULT NULL,
  `desc_opt` varchar(45) DEFAULT NULL,
  `mongo_opt` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_operators_lib`
--

LOCK TABLES `tab_operators_lib` WRITE;
/*!40000 ALTER TABLE `tab_operators_lib` DISABLE KEYS */;
INSERT INTO `tab_operators_lib` VALUES (1,1,'==','Ugualianza','$eq'),(2,2,'<','Minore','$lt'),(3,3,'<=','Minore e uguale','$lte'),(4,4,'>=','Maggiore e uguale','$gte'),(5,5,'!=','Diverso','$ne'),(6,6,'>','Maggiore','$gt');
/*!40000 ALTER TABLE `tab_operators_lib` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_param_lib`
--

DROP TABLE IF EXISTS `tab_param_lib`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_param_lib` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_param` int(11) DEFAULT NULL,
  `param_name` varchar(45) DEFAULT NULL,
  `param_desc` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_param_lib`
--

LOCK TABLES `tab_param_lib` WRITE;
/*!40000 ALTER TABLE `tab_param_lib` DISABLE KEYS */;
INSERT INTO `tab_param_lib` VALUES (1,1,'abst','Parametro abst');
/*!40000 ALTER TABLE `tab_param_lib` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_pipeline`
--

DROP TABLE IF EXISTS `tab_pipeline`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_pipeline` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_user` int(11) DEFAULT NULL,
  `id_pipeline` int(11) DEFAULT NULL,
  `id_task` int(11) DEFAULT NULL,
  `pipeline_desc` varchar(45) DEFAULT NULL,
  `task_desc` varchar(45) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `task_pid` varchar(45) DEFAULT NULL,
  `task_exe` varchar(45) DEFAULT NULL,
  `root_file` varchar(45) DEFAULT NULL,
  `png_file` varchar(45) DEFAULT NULL,
  `last_start` datetime DEFAULT NULL,
  `creation_date` datetime DEFAULT NULL,
  `id_error` int(11) DEFAULT '0',
  `desc_error` varchar(200) DEFAULT NULL,
  `query_mongo` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_pipeline`
--

LOCK TABLES `tab_pipeline` WRITE;
/*!40000 ALTER TABLE `tab_pipeline` DISABLE KEYS */;
INSERT INTO `tab_pipeline` VALUES (5,3,1234,12,'PipeLine Test','ROOT1',6,'23230','pamelaroot','default.root','test.png','2016-03-25 11:13:38','2016-03-23 00:00:00',0,'\"\"','{abstime: {$gt: 1} }');
/*!40000 ALTER TABLE `tab_pipeline` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_status_lib`
--

DROP TABLE IF EXISTS `tab_status_lib`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_status_lib` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_status` int(11) DEFAULT NULL,
  `descr_status` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_status_lib`
--

LOCK TABLES `tab_status_lib` WRITE;
/*!40000 ALTER TABLE `tab_status_lib` DISABLE KEYS */;
INSERT INTO `tab_status_lib` VALUES (1,1,'Working'),(2,2,'Finished'),(3,3,'Stalled'),(4,4,'Error'),(5,5,'Undefined'),(6,6,'To be submitted'),(7,7,'Submitted');
/*!40000 ALTER TABLE `tab_status_lib` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_task`
--

DROP TABLE IF EXISTS `tab_task`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_task` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_task` int(11) DEFAULT NULL,
  `name_task` varchar(45) DEFAULT NULL,
  `path_task` varchar(200) DEFAULT NULL,
  `desc_task` varchar(200) DEFAULT NULL,
  `exec_task` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='Tabella contenente la lista dei task per Pamela-Mongo-Root';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_task`
--

LOCK TABLES `tab_task` WRITE;
/*!40000 ALTER TABLE `tab_task` DISABLE KEYS */;
INSERT INTO `tab_task` VALUES (1,13,'Pamela Root','/software/pamela/bin/','Task prototipo','pamelaroot');
/*!40000 ALTER TABLE `tab_task` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_task_param`
--

DROP TABLE IF EXISTS `tab_task_param`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_task_param` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_task` int(11) DEFAULT NULL,
  `id_param` int(11) DEFAULT NULL,
  `order_param` int(11) DEFAULT NULL,
  `name_param_web` varchar(45) DEFAULT NULL,
  `name_param_mongo` varchar(45) DEFAULT NULL,
  `desc_param` varchar(45) DEFAULT NULL,
  `tool_tip` varchar(1000) DEFAULT NULL,
  `type_param` varchar(45) DEFAULT NULL,
  `value_min` int(11) DEFAULT NULL,
  `value_max` int(11) DEFAULT NULL,
  `value_len` int(11) DEFAULT NULL,
  `value_placeholder` varchar(45) DEFAULT NULL,
  `value_default` int(11) DEFAULT NULL,
  `param_enabled` int(11) DEFAULT NULL,
  `param_visible` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_task_param`
--

LOCK TABLES `tab_task_param` WRITE;
/*!40000 ALTER TABLE `tab_task_param` DISABLE KEYS */;
INSERT INTO `tab_task_param` VALUES (6,13,1,3,'Lon','lon','Longitude','Enter the longitude intervals with any conditions.<br>Longitudes range from -180 to 180.','3',-180,180,4,'0',0,1,1),(7,13,2,2,'Lat','lat','Latitude','Enter the latitude intervals with any conditions.<br>Latitudes range from -90 to 90.','3',-90,90,3,'0',0,1,1),(8,13,3,1,'Time','abstime','Time (GMT)','Enter the time intervals with any conditions.','1',0,0,19,'2000-10-06 19:00:00',0,1,1),(10,13,4,4,'Alt','alt','Altitude','Enter the altitude intervals with any conditions.','1',0,0,5,'0',0,1,1);
/*!40000 ALTER TABLE `tab_task_param` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_task_param_query`
--

DROP TABLE IF EXISTS `tab_task_param_query`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_task_param_query` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_task` int(11) DEFAULT NULL,
  `id_user` int(11) DEFAULT NULL,
  `id_pipeline` int(11) DEFAULT NULL,
  `id_param` int(11) DEFAULT NULL,
  `type_param` int(11) DEFAULT NULL,
  `id_operator` int(11) DEFAULT NULL,
  `value_param` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_task_param_query`
--

LOCK TABLES `tab_task_param_query` WRITE;
/*!40000 ALTER TABLE `tab_task_param_query` DISABLE KEYS */;
/*!40000 ALTER TABLE `tab_task_param_query` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_type_lib`
--

DROP TABLE IF EXISTS `tab_type_lib`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_type_lib` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_type` int(11) DEFAULT NULL,
  `type_desc` varchar(45) DEFAULT NULL,
  `mongo_type` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_type_lib`
--

LOCK TABLES `tab_type_lib` WRITE;
/*!40000 ALTER TABLE `tab_type_lib` DISABLE KEYS */;
INSERT INTO `tab_type_lib` VALUES (1,0,'int','BCON_INT32'),(2,1,'double',NULL),(3,2,'string',NULL);
/*!40000 ALTER TABLE `tab_type_lib` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tab_users`
--

DROP TABLE IF EXISTS `tab_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tab_users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_user` int(11) DEFAULT NULL,
  `login` varchar(45) DEFAULT NULL,
  `name` varchar(45) DEFAULT NULL,
  `user_desc` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tab_users`
--

LOCK TABLES `tab_users` WRITE;
/*!40000 ALTER TABLE `tab_users` DISABLE KEYS */;
INSERT INTO `tab_users` VALUES (1,1,'raffo','Raffaele','developer'),(2,3,'valeria','Valeria','test');
/*!40000 ALTER TABLE `tab_users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'pamelamongodev'
--

--
-- Dumping routines for database 'pamelamongodev'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-06-23  9:00:46
