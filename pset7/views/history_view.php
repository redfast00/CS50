<div>
    <h2>
        <?= $cash?>
    </h2>
    <table class="table table-bordered">
        <tr>
            <th>Action</th>
            <th>Symbol</th>
            <th>Time</th>
            <th>Shares</th>
            <th>Price per share</th>
            <th>Cashflow</th>
        </tr>
    <?php foreach ($positions as $position): ?>
    
        <tr>
            <td><?= ($position["total"] < 0 ? "BUY" : "SELL") ?></td>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["timestamp"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["price"] ?>$</td>
            <td style="color: <?= ($position["total"] < 0 ? "red" : "green") ?>"><?= $position["total"] ?>$</td>
        </tr>
    
    <?php endforeach ?>
    </table>
</div>
