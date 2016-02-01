<h2><?= $cash ?>$</h2>
<p>Get <?= $reward ?>$ for a link to an image of a cat (any image will do, but I really like cats)</p>
<form action="deposit.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="url" placeholder="http://example.com/cat.jpg" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Deposit
            </button>
        </div>
    </fieldset>
</form>