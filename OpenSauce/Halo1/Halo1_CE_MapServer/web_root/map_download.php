<?php
/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
	require_once('hce_map_server/admin/includes/load_config.php');
	require_once('hce_map_server/admin/includes/open_database.php');
	require_once('hce_map_server/admin/includes/sql_interface.php');

	class MapEntryReader extends SQLInterface
	{
		public $file_id;
		public $map_name;
		public $map_extension;
		public $map_compression_stage;
		public $map_compression_type;
		public $map_md5;
		public $map_parts_path;
		public $map_part_count;
		
		public function MapEntryReader($database, $sql) { parent::__construct($database, $sql, SQLInterfaceType::SQL_IO_TYPE_READ); }
	};
	
	class PartEntryReader extends SQLInterface
	{
		public $part_name;
		public $part_md5;
		
		public function PartEntryReader($database, $sql) { parent::__construct($database, $sql, SQLInterfaceType::SQL_IO_TYPE_READ); }
	};
	
	function SendMapPartDefinition(&$map_entry, $database)
	{		
		// build the xml document
		$xml_document = new DOMDocument("1.0", "UTF-8");
		
		$xml_root = $xml_document->createElement("osHTTPServer");
		$xml_root = $xml_document->appendChild($xml_root);
		
		$map_download = $xml_document->createElement("map_download");
		$map_download = $xml_root->appendChild($map_download);
		
		switch($map_entry->map_compression_type)
		{
		case 1:
			$map_download->setAttribute("algorithm", "7zip");
			break;
		default:
			$map_download->setAttribute("algorithm", "zip");
		};

		$map_download->setAttribute("name", $map_entry->map_name.'.'.$map_entry->map_extension);
		$map_download->setAttribute("md5", $map_entry->map_md5);
		
		// get the number of parts and add them to the xml in order
		$part_count = $map_entry->map_part_count;
		
		// set up the part query
		$part_entry = new PartEntryReader($database, "SELECT {0} FROM `map_part_list` WHERE map_file_id = ? AND part_id = ?");
		
		for($i = 0; $i < $part_count; $i++)
		{
			// find the part in the database
			$part_entry->ExecuteQuery(array($map_entry->file_id, $i));
			if(!$part_entry->MoveNext())
			{
				// if the part could not be found, do not return any data
				header("HTTP/1.0 404 Not Found");
				die();
			}
			
			// set the xml element for the part
			$part = $xml_document->createElement("part");
			$part = $map_download->appendChild($part);
			
			$part->setAttribute("name", $part_entry->part_name);
			$part->setAttribute("index", $i);
			$part->setAttribute("md5", $part_entry->part_md5);
		}
		
		// set the xml as the response data
		header("Content-type: text/xml");
		print($xml_document->saveXML());
	}

	function SendMapPartRedirect($map_entry, $map_part_name)
	{
		global $config;
		
		// send a redirect to the map part back to the client
		header("Location: ".$config->map_server->server_address."/".$map_entry->map_parts_path."/".$map_part_name);
	}
	
	// open the sql database
	$database = OpenDatabase($config->map_database->data_source_name,
		$config->map_database->username,
		$config->map_database->password);
		
	$map_name_set = isset($_REQUEST['map']) && !empty($_REQUEST['map']);
	$map_part_set = isset($_REQUEST['part']) && !empty($_REQUEST['part']);

	// the client is requesting a map part if both the map and part queries are set
	// the client is requesting a map part definition if only the map query is set
	if($map_name_set)
	{
		$map_entry = new MapEntryReader($database, "SELECT {0} FROM `map_list` WHERE LOWER(map_name) = LOWER(?)");
		$map_entry->ExecuteQuery(array($_REQUEST['map']));
		
		if(!$map_entry->MoveNext() || ($map_entry->map_compression_stage != 1))
			header("HTTP/1.0 404 Not Found");
		else
		{
			if($map_part_set)
				SendMapPartRedirect($map_entry, $_REQUEST['part']);
			else
				SendMapPartDefinition($map_entry, $database);
		}
	}

	$database = NULL;
?>