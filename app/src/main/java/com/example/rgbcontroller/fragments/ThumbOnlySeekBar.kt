package com.example.rgbcontroller.fragments

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.drawable.Drawable
import android.view.MotionEvent
import android.widget.SeekBar


@SuppressLint("AppCompatCustomView")
class ThumbOnlySeekBar(context: Context?) : SeekBar(context) {
    private var mThumb: Drawable? = null

    override fun setThumb(thumb: Drawable?) {
        super.setThumb(thumb)
        mThumb = thumb
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onTouchEvent(event: MotionEvent): Boolean {
        return if (!mThumb!!.bounds.contains(
                event.x.toInt(),
                event.y.toInt()
            )
        ) true else super.onTouchEvent(event)
    }
}