<div>
    
<table class="table table-hover">
    <thead>
      <tr>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
        <th>TOTAL</th>
      </tr>
    </thead>
    <?php foreach ($positions as $position): ?>
    <?php setlocale(LC_MONETARY, 'en_US.UTF-8') ?>
    <tbody>
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= "$ ".number_format($position["price"], 2); ?></td>
            <td><?= "$ ".number_format($position["price"]*$position["shares"], 2); ?></td>
        </tr>        
    </tbody>

    <?php endforeach ?>
    
    <tr>
        <td>CASH</td>
        <td></td>
        <td></td>
        <td><?= "$ ".number_format($balance, 2); ?></td>
    </tr>

</table>

</div>
