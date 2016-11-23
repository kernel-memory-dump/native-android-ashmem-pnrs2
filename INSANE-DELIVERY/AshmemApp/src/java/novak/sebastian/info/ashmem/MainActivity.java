
/***************************************************************************
 *
 *
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                 Version 2, December 2004
 *
 *      Everyone is permitted to copy and distribute verbatim or modified
 *      copies of this license document, and changing it is allowed as long
 *      as the name is changed.
 *
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE, TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *         0. You just DO WHAT THE FUCK YOU WANT TO
 *
 *  -----------------------------------------------------
 *  Sebastian Novak @ GitHub https://github.com/kernel-memory-dump
 *  -----------------------------------------------------
 *
 *
 * @author  Sebastian Novak
 *
 *
 ****************************************************************************/


package novak.sebastian.info.ashmem;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import novak.sebastian.info.ashmem.presenter.MainPresenter;
import novak.sebastian.info.ashmem.presenter.MainPresenterImpl;
import novak.sebastian.info.ashmem.view.MainView;

public class MainActivity extends Activity implements MainView {

    private static final String TAG = MainActivity.class.getName();

    private MainPresenter presenter;

    private EditText txtImagePath;
    private Button btnLoadImage;
    private Button btnSelectImage;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        presenter = new MainPresenterImpl(this);
        bindUI();

    }

    private void bindUI() {

        txtImagePath = (EditText) findViewById(R.id.txtImagePath);
        btnLoadImage = (Button) findViewById(R.id.btnLoadImage);
        btnSelectImage = (Button) findViewById(R.id.btnSelectImage);

        Button.OnClickListener btnLoadImageClickListener = new Button.OnClickListener() {
            public void onClick(View v) {
                presenter.onLoadImage();
            }
        };

        Button.OnClickListener btnImageSelectClickListener = new Button.OnClickListener() {
            public void onClick(View v){
                presenter.onSelectImage();
            }
        };

        btnLoadImage.setOnClickListener(btnLoadImageClickListener);
        btnSelectImage.setOnClickListener(btnImageSelectClickListener);


        txtImagePath.setText("/data/data/bbt.jpg");

        presenter.onUIReady();

    }



    @Override
    public void setUIEnabled(boolean enabled) {
        Log.v(TAG, "Setting UI enabled to:" + enabled);
        btnLoadImage.setEnabled(enabled);
        btnSelectImage.setEnabled(enabled);
    }

    @Override
    public void setImagePath(String path) {
        txtImagePath.setText(path);
    }

    @Override
    public void showToast(String text) {
        Toast.makeText(getApplicationContext(), text, Toast.LENGTH_LONG).show();
    }

    @Override
    public Activity asActivity() {
        return this;
    }


    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        presenter.onImageSelected(requestCode, resultCode, data);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
