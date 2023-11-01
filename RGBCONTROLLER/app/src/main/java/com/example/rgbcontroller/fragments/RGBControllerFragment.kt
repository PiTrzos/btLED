package com.example.rgbcontroller.fragments

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.viewpager.widget.ViewPager
import com.example.rgbcontroller.R
import com.google.android.material.tabs.TabLayout


class RGBControllerFragment : Fragment() {
    private lateinit var rGBControllerPagerAdapter: RGBControllerPagerAdapter
    private lateinit var viewPager: CustomViewPager
    private lateinit var tabLayout: TabLayout

    override fun onCreateView(inflater: LayoutInflater,
                              container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.rgbcontroller_fragment, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        rGBControllerPagerAdapter = RGBControllerPagerAdapter(childFragmentManager)

        viewPager =  view.findViewById(R.id.pager) as CustomViewPager
        tabLayout = view.findViewById(R.id.tab_layout)

        viewPager.offscreenPageLimit = 2

        tabLayout.setupWithViewPager(viewPager)

        viewPager.adapter = rGBControllerPagerAdapter
    }

}
