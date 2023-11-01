package com.example.rgbcontroller.models

import androidx.annotation.DrawableRes

data class RGBMode(
    val id: Int,
    val name: String,
    val note: String,
    @DrawableRes
    val resId: Int
)
