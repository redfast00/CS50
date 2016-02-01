<div>
    <h2><?= $cash?>$</h2>
    <?php if (count($positions) > 0): ?>
    <table class="table table-bordered">
        <tr>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    <?php foreach ($positions as $position): ?>
    
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["price"] ?></td>
        </tr>
    
    <?php endforeach ?>
    <?php endif ?>
    </table>
</div>
