//
//  ViewController.swift
//  TestOpenCVSwift
//
//  Created by 上田 純也 on 5/20/16.
//  Copyright © 2016 uejun. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var opencvVersionLabel: UILabel!
    @IBOutlet weak var lenaImageView: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        opencvVersionLabel.text = OpenCVWrapper.opencvVersionString()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func tapGrayScaleButton(sender: AnyObject) {
        lenaImageView.image = OpenCVWrapper.makeGrayImageFromUIImage(lenaImageView.image);
    }

}

