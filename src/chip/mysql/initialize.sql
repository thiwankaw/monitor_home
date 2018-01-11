CREATE DATABASE `sensor_data` /*!40100 DEFAULT CHARACTER SET latin1 */;


CREATE TABLE `samples` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `createdTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `application` varchar(20) COLLATE latin1_bin DEFAULT NULL,
  `skey` varchar(20) COLLATE latin1_bin DEFAULT NULL,
  `svalue` varchar(20) COLLATE latin1_bin DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=142120 DEFAULT CHARSET=latin1 COLLATE=latin1_bin;


CREATE ALGORITHM=UNDEFINED DEFINER=`data_user`@`localhost` SQL SECURITY DEFINER
VIEW `current` AS select `samples`.`createdTime` AS `createdTime`,`samples`.`svalue` AS `svalue`
from `samples` where ((`samples`.`skey` = 'current') and (`samples`.`svalue` >= 0));

CREATE ALGORITHM=UNDEFINED DEFINER=`data_user`@`localhost` SQL SECURITY DEFINER
VIEW `pressure` AS select `samples`.`createdTime` AS `createdTime`,`samples`.`svalue` AS `svalue`
from `samples` where (`samples`.`skey` = 'pressure');

CREATE ALGORITHM=UNDEFINED DEFINER=`data_user`@`localhost` SQL SECURITY DEFINER
VIEW `temperature` AS select `samples`.`createdTime` AS `createdTime`,`samples`.`svalue` AS `svalue`
from `samples` where (`samples`.`skey` = 'temperature');