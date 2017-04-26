<?php

	include_once("FeedWriter.php");
	include_once("variables.php");
	include_once("functions.php");
	
	$author = 'Hossam Hammady (podcasts@hammady.net)';
	$summary = 'بالعربي، بث تجريبي أتحدث فيه أسبوعيا عن أحدث الأخبار المتعلقة بالإنترنت والجوال وتكنولوجيا المعلومات بصفة عامة.
	سأبدأ بإذن الله ببث تجريبي أسبوعيا، ألقي الضوء فيه على ما يجد في هذا المجال';
	
	$feedObj = new FeedWriter(RSS2);

	//Setting the channel elements
	//Use wrapper functions for common channel elements
	$feedObj->setTitle('بالعربي، أحدث الأخبار التقنية');
	$feedObj->setLink('http://podcasts.hammady.net');
	$feedObj->setDescription($summary);

	//Use core setChannelElement() function for other optional channels
	$feedObj->setChannelElement('language', 'ar-eg');
	$feedObj->setChannelElement('pubDate', date(DATE_RSS, time()));
	$feedObj->setChannelElement('itunes:author', $author);
	$feedObj->setChannelElement('itunes:summary', $summary);
	
	@mysql_connect($hostname, $username, $password) or die('DB ERROR');
	@mysql_select_db($dbname) or die('DB ERROR');
	mysql_query("SET NAMES 'utf8'");	// mandatory because we cannot convert the server encoding
	
	$query = "select * from podcasts where enabled = 1 order by id";
	
	$result = mysql_query($query);

	while($row = mysql_fetch_array($result, MYSQL_ASSOC))
	{
		$newItem = $feedObj->createNewItem();

		/*$duration = round($row['duration'] / 60);
		if ($duration <= 10)
			$min = "دقائق";
		else
			$min = "دقيقة";*/

		$newItem->setTitle($row['title']/* . " - $duration $min"*/);
		$newItem->setLink($row['url']);
		$newItem->setDate($row['created_on']);
		$newItem->setDescription($row['descr']);
		$newItem->setEncloser($row['url'], $row['size'], 'audio/mpeg');
		$newItem->addElement('author', $author);
		$newItem->addElement('guid', $row['url'], array('isPermaLink'=>'true'));
		
		// iTunes specific
		$newItem->addElement('itunes:author', $author);
		$newItem->addElement('itunes:summary', $row['descr']);

		$feedObj->addItem($newItem);
	}

	mysql_close();
	
	//OK. Everything is done. Now genarate the feed.
	$feed = $feedObj->genarateFeed(true, true);
	
	// Now write the feed to a file
	writeFeed($feedXMLFileName, $feed);
		
?>
