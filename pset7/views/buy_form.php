<h2><?= $cash ?>$</h2>
<form action="buy.php" method="post">
    <fieldset>
        
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="SYMBOL" type="text"/>
        </div>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="shares" placeholder="Amount" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Buy
            </button>
        </div>
    </fieldset>
</form>