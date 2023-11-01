package com.example.rgbcontroller.fragments

import android.annotation.SuppressLint
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.SeekBar
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.rgbcontroller.BlueToothAllInOne
import com.example.rgbcontroller.R
import com.example.rgbcontroller.adapters.ModeAdapter
import com.example.rgbcontroller.databinding.ModeFragmentBinding
import com.example.rgbcontroller.models.RGBMode
import kotlin.concurrent.thread


class ModesFragment: Fragment() {
    private lateinit var binding: ModeFragmentBinding
    private lateinit var adapter: ModeAdapter

    private var modeList: List<RGBMode> = listOf(
        RGBMode(1,"Fade", "Change colors of all LEDS cycle", R.drawable.rainbow),
        RGBMode(2,"Rainbow", "Simulates RGB rainbow", R.drawable.rainbow),
        RGBMode(3,"Breathing", "Simulates breathing of a human", R.drawable.rainbow),
        RGBMode(4,"Rainbow Stripe", "RGB rainbow stripes", R.drawable.rainbow),
        RGBMode(5,"Ocean Gradient", "Blue colors", R.drawable.rainbow),
        RGBMode(6,"Flash", "Quick color changes", R.drawable.rainbow),
        RGBMode(7,"Ping Pong", "ping pong", R.drawable.rainbow),
        RGBMode(8,"Lasers", "lasers", R.drawable.rainbow),
        RGBMode(9,"Sparkle", "sparkles", R.drawable.rainbow),
        RGBMode(10,"Music", "Music reactive", R.drawable.rainbow),
        RGBMode(11,"Ambient Lightning", "ambient", R.drawable.rainbow)
    )

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return ModeFragmentBinding.inflate(inflater, container, false).also {
            binding = it
        }.root
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        adapter = ModeAdapter()

        binding.deviceList.let {
            it.adapter = adapter
            it.layoutManager = LinearLayoutManager(requireContext())
        }
        binding.speedSeekBar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener{
            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                if (BlueToothAllInOne.OutputCalculated.get()){
                    BlueToothAllInOne.sendToAll("S${100-progress}\n") //maybe delay?
                }
            }

            override fun onStartTrackingTouch(seekBar: SeekBar) {
                // you can probably leave this empty
            }

            override fun onStopTrackingTouch(seekBar: SeekBar) {
                // you can probably leave this empty
            }
        })
    }

    override fun onStart() {
        super.onStart()
        loadData()
    }

    private fun loadData() {
        thread {
            val modes = modeList.map {entity->
                RGBMode(
                    entity.id,
                    entity.name,
                    entity.note,
                    entity.resId
                )
            }
            modes.let { adapter.replace(it) }
        }
    }
}