<?php
	require($_SERVER['DOCUMENT_ROOT'].'/includes/config.inc');
	$meta = decode_json(realpath("meta.json"));
	extract($meta, EXTR_OVERWRITE);
	setPageTitle($title);
	require("../../resources/template.inc");
?>