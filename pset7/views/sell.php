<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
          <select class="form-control" name="symbol">
            <option disabled selected>Symbol</option>
            <?php
            foreach($symbols as $symbol):
            echo '<option value="'.$symbol["symbol"].'">'.$symbol["symbol"].'</option>'; 
            endforeach;
            ?>
          </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Sell
            </button>
        </div>
    </fieldset>
</form>
