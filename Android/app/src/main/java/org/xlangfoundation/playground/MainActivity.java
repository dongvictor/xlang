package org.xlangfoundation.playground;

import android.app.Fragment;
import android.content.res.AssetManager;
import android.os.Bundle;

import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;

import android.util.Log;
import android.view.View;

import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import org.xlangfoundation.playground.databinding.ActivityMainBinding;

import android.view.Menu;
import android.view.MenuItem;
import  org.xlangfoundation.playground.xlang;

import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private AppBarConfiguration appBarConfiguration;
    private ActivityMainBinding binding;
    private  xlang _xlang;

    private String StreamToString(InputStream is) {
        final int bufferSize = 1024;
        final char[] buffer = new char[bufferSize];
        final StringBuilder out = new StringBuilder();
        try {
            Reader in = new InputStreamReader(is, "UTF-8");
            for (; ; ) {
                int rsz = in.read(buffer, 0, buffer.length);
                if (rsz < 0)
                    break;
                out.append(buffer, 0, rsz);
            }
        } catch (Exception e) {
            e.printStackTrace();
            Log.e("ERR ", e.getMessage());
        } catch (OutOfMemoryError e) {
            e.printStackTrace();
        }
        return out.toString();
    }
    @Override
    public void onAttachFragment(Fragment fragment) {
        String code ="";
    }
    public Fragment CreateFragment()
    {
        List<Fragment> fs = getFragmentManager().getFragments();
        return fs.get(0);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        String code ="";
        AssetManager am = getAssets();
        try {
            InputStream is = am.open("playground.x");
            code = StreamToString(is);
        } catch (Exception e) {
            e.printStackTrace();
            Log.e("ERR ", e.getMessage());
        } catch (OutOfMemoryError e) {
            e.printStackTrace();
        }
        _xlang = new xlang(this);
        try {
            Class c = _xlang.getClass();
            Method[] l = c.getDeclaredMethods();
            String s = Arrays.toString(l);
            Log.i("test",s);
        }
        catch (Exception e)
        {

        }
        boolean retVal = _xlang.loadJNI();
        _xlang.runJNI(code);
        //_xlang.unloadJNI();

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        setSupportActionBar(binding.toolbar);

        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment_content_main);
        appBarConfiguration = new AppBarConfiguration.Builder(navController.getGraph()).build();
        NavigationUI.setupActionBarWithNavController(this, navController, appBarConfiguration);

        binding.fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
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

    @Override
    public boolean onSupportNavigateUp() {
        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment_content_main);
        return NavigationUI.navigateUp(navController, appBarConfiguration)
                || super.onSupportNavigateUp();
    }
}