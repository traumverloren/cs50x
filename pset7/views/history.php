<div>
    
<table class="table table-hover">
    <thead>
      <tr>
        <th>Transaction</th>
        <th>Date/Time</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
      </tr>
    </thead>
    <?php foreach ($positions as $position): ?>
    <?php setlocale(LC_MONETARY, 'en_US.UTF-8') ?>
        <tbody>
            <tr>
                <td><?= $position["transaction_type"] ?></td>
                <td><?= $position["created_at"] ?></td>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= "$ ".number_format($position["price"], 2); ?></td>
            </tr>        
        </tbody>
    <?php endforeach ?>
</table>

</div>
