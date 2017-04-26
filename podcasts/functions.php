<?php
	function writeFeed($filename, $content) {
		if (!$handle = fopen($filename, 'w'))
		     die("خطأ في فتح الملف ($filename)");
		$size = fwrite($handle, $content);
		if ($size === FALSE)
		    die("خطأ في كتابة البيانات على الملف");
		echo "تمت كتابة $size بايت بنجاح على الملف $filename.<br/>";
		fclose($handle);
	}
?>
