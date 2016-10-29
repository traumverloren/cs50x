<h1><?= $name ?> (<?= strtoupper($symbol) ?>)</h1>
<h3>Current Price: <?= "$ ".number_format($price, 2);  ?></h3>
<br />
<br />
<div>
    Get another <a href="quote.php">quote</a>?
</div>