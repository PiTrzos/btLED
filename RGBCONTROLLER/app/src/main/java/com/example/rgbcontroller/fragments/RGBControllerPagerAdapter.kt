package com.example.rgbcontroller.fragments

import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter

class RGBControllerPagerAdapter(fm: FragmentManager) : FragmentPagerAdapter(fm){
    private val mFragList: List<Fragment> = listOf(
        ConnectedDevicesFragment(),
        StaticLightningFragment(),
        ModesFragment()
    )

    private val mFragList2: List<String> = listOf(
        "Connected Devices",
        "Static Light",
        "Modes"
    )

    override fun getCount(): Int  = 3

    override fun getItem(i: Int): Fragment {
        return when(i){
            0 -> mFragList[0]
            1 -> mFragList[1]
            2 -> mFragList[2]
            else ->{
                mFragList[0]
            }
        }
    }

    override fun getPageTitle(position: Int): CharSequence {
        return when(position){
            0 -> mFragList2[0]
            1 -> mFragList2[1]
            2 -> mFragList2[2]
            else ->{
                mFragList2[0]
            }
        }
    }

}
