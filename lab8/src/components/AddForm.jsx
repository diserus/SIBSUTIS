import React from 'react';
import { Formik, Form, Field, ErrorMessage } from 'formik';
import * as Yup from 'yup';

const AddForm = ({ initialValues, validationSchema, onSubmit, fields }) => (
  <Formik initialValues={initialValues} validationSchema={validationSchema} onSubmit={onSubmit}>
    <Form style={{ padding: '10px', border: '1px solid #ccc', marginBottom: '20px' }}>
      {fields.map(({ name, label, type }) => (
        <div key={name} style={{ marginBottom: '10px' }}>
          <label>{label}:</label>
          <Field name={name} type={type || 'text'} style={{ width: '100%', padding: '8px' }} />
          <ErrorMessage name={name} component="div" style={{ color: 'red' }} />
        </div>
      ))}
      <button type="submit">Submit</button>
    </Form>
  </Formik>
);

export default AddForm;
