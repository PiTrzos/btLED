package com.example.rgbcontroller


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.rgbcontroller.fragments.*


class MainActivity : AppCompatActivity(),Navigable {
    private lateinit var connectionFragment: ConnectionFragment

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        connectionFragment = ConnectionFragment()

        supportFragmentManager.beginTransaction()
            .add(R.id.ConstraintLayout,connectionFragment,connectionFragment.javaClass.name)
            .commit()
    }

    override fun navigate(to: Navigable.Destination){
        supportFragmentManager.beginTransaction().apply {
            when(to){
                Navigable.Destination.List -> {
                    replace(R.id.ConstraintLayout,RGBControllerFragment(),RGBControllerFragment::class.java.name)
                }
            }
        }.commit()
    }
}