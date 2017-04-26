<?
	header("Content-type: text/html; charset=utf-8");
?>
<html>
	<head>
		<script type="text/javascript">
			function validateForm() {
				var title = document.getElementById('title');
				var descr = document.getElementById('descr');
				var password = document.getElementById('password');
				if (!title.value) {
					alert("عنوان الحلقة مطلوب");
					title.focus();
					return false;
				}
				if (!descr.value) {
					alert("تفاصيل الحلقة مطلوبة");
					descr.focus();
					return false;
				}
				if (!password.value) {
					alert("كلمة المرور مطلوبة");
					password.focus();
					return false;
				}
				return true;
			}
		</script>
		<title>
			شاشة إدارة الأخبار التكنولوجية بالعربي
		</title>
	</head>
<body dir="rtl">
<?
#insert record in the podcasts table

function displayForm() {
?>
	<form method="POST" onsubmit="return validateForm();" enctype="multipart/form-data">
		<input type="hidden" name="process" />
		<p>عنوان الحلقة:<br/>
			<input type="text" name="title" id="title" size="128" value=""/>
		</p>
		<p>تفاصيل الحلقة:<br/>
			<textarea name="descr" rows="20" id="descr" cols="113"></textarea>
		</p>
		<p>مادة الحلقة:<br/>
			<input type="file" name="media" />
		</p>
		<p>كلمة المرور:<br/>
			<input type="password" name="password" id="password" size="16" value=""/>
		</p>
		<p>
			<input type="submit" value="إضافة الحلقة" />
		</p>
	</form>
<?
}

function insert($fileName, $fileSize, $title, $descr) {
	include("variables.php");
	@mysql_connect($hostname, $username, $password) or die('DB ERROR');
	@mysql_select_db($dbname) or die('DB ERROR');
	mysql_query("SET NAMES 'utf8'");	// mandatory because we cannot convert the server encoding
	$title = mysql_real_escape_string($title);
	$url = "http://hammady.net/media/$fileName";
	$descr = mysql_real_escape_string($descr);
	
	$query = "INSERT INTO podcasts (title, url, created_on, descr, ".
		"size, enabled) VALUES (".
		"'$title', '$url', NOW(), '$descr', $fileSize, 1".
		")";
	if (!mysql_query($query)) {
		echo "خطأ في تعديل قاعدة البيانات."."<br/>";
		mysql_close();
	}
	else {
		echo "تم عملية تعديل قاعدة البيانات بنجاح."."<br/>";
		mysql_close();
		include("generate-feeds-xml.php");
?>
		<a href="https://phobos.apple.com/WebObjects/MZFinance.woa/wa/pingPodcast?id=360549324">اضغط هنا لتحديث دليل آيتيونز - ping iTunes directory</a>
<?
	}
	

}

function process() {
	include("variables.php");
	if ($_POST['password'] != $password) {
		echo "عذرا، غير مسموح باستخدام هذه الخدمة إلا للمصرح لهم" . "<br/>";
		return;
	}
	
	if ($_FILES["media"]["error"] > 0)
	{
		echo "هناك مشكلة في رفع الملف: " . $_FILES["media"]["error"] . "<br/>";
	}
	else
	{
		if ($_FILES["media"]["size"] == 0) {
			echo "الملف غير موجود أو فارغ." . "<br/>";
			return;
		}

		if (file_exists("../media/" . $_FILES["media"]["name"]))
		{
			echo $_FILES["media"]["name"] . " موجود بالفعل. من فضلك حاول مرة أخرى وذلك باختيار اسم آخر للملف.". "<br/>";
		}
		else
		{
			if (move_uploaded_file($_FILES["media"]["tmp_name"],
			"../media/" . $_FILES["media"]["name"]) == FALSE) {
				echo "خطأ: توجد مشكلة في حفظ الملف في مكانه النهائي.";
				return;
			}
			echo "تمت عملية رفع الملف بنجاح." . "<br/>"; 
			insert($_FILES["media"]["name"], $_FILES["media"]["size"],
			  $_POST['title'], $_POST['descr']);
		}
	}
}

if (isset($_POST['process']))
	process();
else
	displayForm();
?>

</body>
</html>
