﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MindWaveExperimentRecorder.CSCExperimentor 
{

    public struct Participant 
    {
        public String Name;

        public Genders Gender;

        public enum Genders { None, Male, Female }

        public Participant(string name, Genders gender)
        {
            Name = name;
            Gender = gender;
        }
    }

    public abstract class DataPoint
    {
        public DateTime TimeStamp;

        protected DataPoint(DateTime time)
        {
            TimeStamp = time;
        }
    }

    public class TypedDataPoint<T> : DataPoint
    {
        public T Value;

        public TypedDataPoint(T val, DateTime time)
            : base(time)
        {
            Value = val;
        }
    }

    interface IExperimentManager
    {
        /// <summary>
        /// Set a new particpant.
        /// Will clear all experiments of the previous participant
        /// </summary>
        /// <param name="name"></param>
        /// <param name="level">Experience level of the candidate</param>
        /// <param name="autoSaveExperiments">Should any previous experiments be saved to an auto generated file?</param>
        void setNewParticipant(string name, Participant.Genders level, bool autoSaveExperiments = true);

        /// <summary>
        /// Starts a new experiment. Unsaved data will be lost
        /// </summary>
        /// <param name="id">unique id for this experiment.</param>
        /// <param name="isVR">Whether the experiment is VR or not</param>
        void startNewExperiment(string id, bool isVR);

        /// <summary>
        /// Adds a new record to the currently running experiment
        /// </summary>
        /// <param name="point">point to be recorded</param>
        /// <param name="id">id for the point, to be used to determine what this point of data is</param>
        void recordPoint(DataPoint point, string id);

        /// <summary>
        /// Sets the recording status
        /// </summary>
        /// <param name="state">True if data should be captures, false if otherwise</param>
        void setRecordData(bool state);

        /// <summary>
        /// Exports all the stored experiment data to a text file
        /// </summary>
        void exportAllExperiments(String filePath);

        /// <summary>
        /// Shuts down the experiment without saving
        /// </summary>
        void shutdown();
    }
}
