package com.example.rgbcontroller.fragments


import android.content.Context
import android.util.AttributeSet
import android.view.DragEvent
import android.view.MotionEvent
import android.view.animation.DecelerateInterpolator
import android.widget.Scroller
import androidx.viewpager.widget.ViewPager
import java.lang.reflect.Field


class CustomViewPager(context: Context, attrs: AttributeSet) : ViewPager(context, attrs) {

    override fun onInterceptTouchEvent(event: MotionEvent?): Boolean {
        return false
    }

    override fun onDragEvent(event: DragEvent?): Boolean {
        return super.onDragEvent(event)
    }

    private fun setMyScroller() {
        try {
            val viewpager: Class<*> = ViewPager::class.java
            val scroller: Field = viewpager.getDeclaredField("mScroller")
            scroller.isAccessible = true
            scroller.set(this, MyScroller(context))
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    class MyScroller(context: Context?) :
        Scroller(context, DecelerateInterpolator()) {
        override fun startScroll(startX: Int, startY: Int, dx: Int, dy: Int, duration: Int) {
            super.startScroll(startX, startY, dx, dy, 350 /*1 secs*/)
        }
    }
}